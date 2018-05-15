import better_exceptions

import copy
import numpy as np
import os.path
import json
import argparse
import math
import cv2
import time
from sklearn.preprocessing import normalize
from moviepy.editor import VideoFileClip, ImageSequenceClip
from sklearn.linear_model import LinearRegression
# from curves import Curves
from lane_detection import LaneDetectionClass

parser = argparse.ArgumentParser()
parser.add_argument('--videopath', type=str)
args = parser.parse_args()

lane_detector = LaneDetectionClass(
    segnet_model='./SegNet/Models/segnet_deploy.prototxt',
    segnet_weights='./SegNet/Models/segnet_weights_driving.caffemodel',
    road_horizon=180,
    camera_height=1.0,
    velocity_max=5.0,
    intrinsic_matrix=np.zeros(shape=(3, 4)),
    use_pointcloud=False,
    use_gpu=False
)

road_images = []
lane_images = []

def segment(frame):
    lane_img, road_img = lane_detector.segment(frame, get_road=True)
    lane_images.append(lane_img)
    road_images.append(road_img)

lines = []

def lane_detect(lane_img):
    # perform segmentation using SegNet
    # lane_img = lane_detector.segment(frame)
    # print(lane_img.shape)

    # detect lanes
    line1_filtered, line2_filtered = lane_detector.detect_and_filter_lanes(
        lane_img)
    lines.append((line1_filtered, line2_filtered))

draw_it = 0
def draw_lines(frame):
    global draw_it
    frame_copy = copy.deepcopy(frame)
    if draw_it < len(lines):
        line1_filtered, line2_filtered = lines[draw_it]
        line_draw1 = None
        line_draw2 = None
        if line1_filtered is not None:
            line_draw1 = (((line1_filtered[0], line1_filtered[1]),
                           (line1_filtered[2], line1_filtered[3])))
        if line2_filtered is not None:
            line_draw2 = (((line2_filtered[0], line2_filtered[1]),
                           (line2_filtered[2], line2_filtered[3])))
        # draw lanes on image
        if line_draw1 and line_draw2:
            lane_detector.draw_lanes(frame_copy, line_draw1, line_draw2)
    draw_it += 1
    return frame_copy


vid_output_segnet = './vid1/output_segnet.mp4'
vid_output_segnet_lane = './vid1/output_segnet_lane.mp4'
vid_output_segnet_road = './vid1/output_segnet_road.mp4'
vid_output_algo = './vid1/output_algo.mp4'

# Segment
input_clip = VideoFileClip(args.videopath)
for input_frame in input_clip.iter_frames():
    segment(input_frame)

# vid_clip = input_clip.fl_image(segment)
# vid_clip.write_videofile(vid_output_segnet, audio=False)

lane_clip = ImageSequenceClip(lane_images, fps=4)
lane_clip.write_videofile(vid_output_segnet_lane, audio=False)
road_clip = ImageSequenceClip(road_images, fps=4)
road_clip.write_videofile(vid_output_segnet_road, audio=False)

# Compute lines

input_clip = VideoFileClip(vid_output_segnet)
for input_frame in input_clip.iter_frames():
    lane_detect(input_frame)
# input_clip.fl_image(lane_detect)


# Draw lines
input_clip = VideoFileClip(args.videopath)
vid_clip = input_clip.fl_image(draw_lines)
vid_clip.write_videofile(vid_output_algo, audio=False)
