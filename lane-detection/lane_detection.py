import copy
import numpy as np
import cv2

caffe_root = './SegNet/caffe-segnet/'
import sys
sys.path.insert(0, caffe_root + 'python')

import caffe

from LaneTracking.detect import LaneDetector
from LaneTracking.track import LaneTracker


class LaneDetectionClass(object):
    def __init__(self, segnet_model, segnet_weights, road_horizon,
                 camera_height, velocity_max, intrinsic_matrix,  # focal length in metres
                 use_pointcloud=True, use_gpu=False, debug=True, output_dir="./debug/"):
        # Segnet initialization
        self.segnet_required_shape = ()
        if use_gpu:
            caffe.set_mode_gpu()
        else:
            caffe.set_mode_cpu()
        self.net = caffe.Net(segnet_model, segnet_weights, caffe.TEST)
        input_shape = self.net.blobs['data'].data.shape
        output_shape = self.net.blobs['argmax'].data.shape
        self.segnet_required_shape = (input_shape[3], input_shape[2])
        # print(self.segnet_required_shape)

        # Lane detection initialization
        self.lane_detector = LaneDetector(road_horizon)
        self.lane_tracker = LaneTracker(2, 0.1, 500)

        # TODO: find out what these variables do!
        self.prec_ticks = 0
        self.ticks = 0

        self.camera_height = camera_height
        self.velocity_max = velocity_max

        self.fx = intrinsic_matrix[0, 0]
        self.fy = intrinsic_matrix[1, 1]
        self.use_pointcloud = use_pointcloud

        # Debugging
        self.debug = debug
        self.output_dir = output_dir

    def segment(self, frame, get_road=False):
        image_shape = frame.shape

        # resize image for segmentation
        frame = cv2.resize(frame, self.segnet_required_shape)

        # BGR -> RGB
        input_image = frame.transpose((2, 0, 1))

        input_image = np.asarray([input_image])

        # Supply image as input to caffe model
        self.net.blobs['data'].data[...] = input_image
        self.net.forward()

        # Selecting lane points and binarization
        segmentation_ind = np.squeeze(
            self.net.blobs['argmax'].data).astype('int')
        road_points = segmentation_ind == 4
        lane_points = segmentation_ind == 3

        # lane_points_3d = np.dstack(
        #     (lane_points, lane_points, lane_points)) * 255
        # lane_points_binarized = lane_points_3d[:, :, 0].astype(np.uint8)
        # lane_image = cv2.resize(lane_points_binarized, (image_shape[0], image_shape[1]))
        lane_image_2d = cv2.resize(
            np.array(lane_points*255, dtype=np.uint8), (image_shape[0], image_shape[1]))
        lane_image = np.dstack((lane_image_2d, lane_image_2d, lane_image_2d))

        road_image_2d = cv2.resize(
            np.array(road_points*255, dtype=np.uint8), (image_shape[0], image_shape[1]))
        road_image = np.dstack((road_image_2d, road_image_2d, road_image_2d))

        if get_road:
            return lane_image, road_image
        else:
            return lane_image

    def detect_and_filter_lanes(self, frame):
        self.prec_ticks = self.ticks
        self.ticks = cv2.getTickCount()
        dt = (self.ticks - self.prec_ticks) / cv2.getTickFrequency()

        predicted = self.lane_tracker.predict(dt)
        lanes = self.lane_detector.detect(frame)

        if lanes is not None:
            # print("Detected lanes in frame")
            self.lane_tracker.update(lanes)

        if predicted is not None:
            return predicted[0], predicted[1]
        else:
            return None, None

    def draw_lanes(self, frame, lines1, lines2, color=(0, 0, 255), thickness=4):
        cv2.line(frame, lines1[0], lines1[1], color, thickness)
        cv2.line(frame, lines2[0], lines2[1], color, thickness)

    def _project_onto_ground(self, point, h, w):
        z = float(self.fy * self.camera_height) / \
            float(point[1] - float(h / 2))
        x = float(z * (point[0] - float(w / 2))) / float(self.fx)
        return x, z

    def get_ground_angle(self, point1, point2, h, w):
        """ returns angle made by line with +z axis with clockwise positive """
        point1_on_ground = self._project_onto_ground(point1, h, w)
        point2_on_ground = self._project_onto_ground(point2, h, w)
        return math.arctan2((point1_on_ground[0] - point2_on_ground[0]),
                            (point1_on_ground[1] - point2_on_ground[1]))

    def process(self, frame, depth_map=None, point_cloud=None):
        # perform segmentation using SegNet
        lane_img = self.segment(frame)

        # detect lanes
        line1_filtered, line2_filtered = self.detect_and_filter_lanes(lane_img)

        if self.debug:
            frame_copy = copy.deepcopy(frame)
            if line1_filtered is not None:
                line_draw1 = (((line1_filtered[0], line1_filtered[1]),
                               (line1_filtered[2], line1_filtered[3])))
            if line2_filtered is not None:
                line_draw2 = (((line2_filtered[0], line2_filtered[1]),
                               (line2_filtered[2], line2_filtered[3])))
            # draw lanes on image
            if line_draw1 and line_draw2:
                self.draw_lanes(frame_copy, line_draw1, line_draw2)
            # dump image to output_dir
            # cv2.imwrite(self.output_dir + 'frames_{}.jpg'.format(), frame)

        # find direction in global co-ordinate system
        if self.use_pointcloud:
            pass
        else:
            h, w = frame.shape()
            line1_ground_angle = self.get_ground_angle((line1_filtered[0], line1_filtered[1]),
                                                       (line1_filtered[2],
                                                        line1_filtered[3]),
                                                       h, w)
            line2_ground_angle = self.get_ground_angle((line2_filtered[0], line2_filtered[1]),
                                                       (line2_filtered[2],
                                                        line2_filtered[3]),
                                                       h, w)
            ground_angle = (line1_ground_angle + line2_ground_angle) / 2
            # print(ground_angle)

        self.get_motion_parameters()
