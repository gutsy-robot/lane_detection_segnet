import numpy as np
import cv2

import pyfly2
import pbcvt

import sys
PYFLY_LIBS_PATH = '/home/quantumcoder/car-project/lane-detection/pyfly2-libs'
sys.path.append(PYFLY_LIBS_PATH)

# load camera parameters
CAM_PARAM_FILE = "cam_params_flycap.yml"
# camparam = aruco.CameraParameters()
# camparam.readFromXMLFile(CAM_PARAM_FILE)

# Initialize camera
context = pyfly2.Context()
if context.num_cameras < 1:
    raise ValueError('No cameras found')
cameraIndex = 0
camera = context.get_camera(cameraIndex)
camera.Connect()
camera.StartCapture()

while True:
    frame_raw = camera.GrabNumPyImage('bgr')
    frame = pbcvt.getUndistortedFrame(frame_raw)

    cv2.imshow('frame', frame)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
