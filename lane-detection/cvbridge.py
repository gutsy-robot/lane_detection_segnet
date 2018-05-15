#!/usr/bin/env python

import numpy as np
import rospy
from sensor_msgs.msg import Image
import cv2
from cv_bridge import CvBridge, CvBridgeError

import lane_detection


class ImageCvBridge(object):
	def __init__(self):
		rospy.loginfo("Changing ROS topic to cv image...")
		self.image_sub = rospy.Subscriber("/zed/rgb/image_rect_color",Image, self.image_callback)
		self.bridge = CvBridge()
		self.lane_detector = lane_detection.LaneDetectionClass(
			segnet_model='./Models/segnet_deploy.prototxt',
			segnet_weights='./Models/segnet_weights_driving.caffemodel',
			road_horizon=200,
			camera_height=1.0,
			velocity_max=1.0,
			intrinsic_matrix=np.asarray([[700.881, 0.0, 0.0, 0.0], [0.0, 700.881, 0.0, 0.0], [0.0, 0.0, 0.0, 0.0]]),
			use_pointcloud=False,
			use_gpu=True
			)

		rospy.loginfo("all objects for ros to cv conversion initialised...")
		rospy.sleep(4)
		

	def image_callback(self, data):
		self.image_data = data



	def run(self):
		cv_image = self.bridge.imgmsg_to_cv2(self.image_data, "bgr8")
		self.lane_detector.process(cv_image)

	def do_work(self):
		r = rospy.Rate(2)
		while not rospy.is_shutdown():
			self.do_work()
			r.sleep()


if __name__ == '__main__':
	rospy.init_node('image_extracter')
	obj = ImageCvBridge()
	obj.run()