from __future__ import division
import better_exceptions

import numpy as np
import cv2
from moviepy.editor import VideoFileClip
import argparse
import json

import track
import detect

# Import arguments
parser = argparse.ArgumentParser()
parser.add_argument('--videopath', type=str, required=True)
args = parser.parse_args()

lt = track.LaneTracker(2, 0.1, 500)
ld = detect.LaneDetector(180)

lines1 = {}
lines2 = {}

it = 0
ticks = 0
iti = 0
def track(frame):
    global lt, ld, ticks, it

    precTick = ticks
    ticks = cv2.getTickCount()
    dt = (ticks - precTick) / cv2.getTickFrequency()

    predicted = lt.predict(dt)
    lanes = ld.detect(frame)

    if predicted is not None:
        lines1[it] = (((predicted[0][0], predicted[0][1]), (predicted[0][2], predicted[0][3])))
        lines2[it] = (((predicted[1][0], predicted[1][1]), (predicted[1][2], predicted[1][3])))

    if lanes is not None:
        lt.update(lanes)

    it += 1
    return frame


def draw(frame):
    global iti
    frame_resized = cv2.resize(frame, (400, 600))
    if iti in lines1 and iti in lines2 and lines1[iti] and lines2[iti]:
        cv2.line(frame_resized, lines1[iti][0], lines1[iti][1], (0, 0, 255), 4)
        cv2.line(frame_resized, lines2[iti][0], lines2[iti][1], (0, 0, 255), 4)

    iti += 1
    return frame_resized


def main():
    # cap = cv2.VideoCapture("/home/quantumcoder/car-project/lane-detection/SegNet/Scripts/IIT_lane_black_lines_half.mp4")
    #
    # ticks = 0
    # while cap.isOpened():
    #     precTick = ticks
    #     ticks = cv2.getTickCount()
    #     dt = (ticks - precTick) / cv2.getTickFrequency()
    #
    #     ret, frame = cap.read()
    #
    #     predicted = lt.predict(dt)
    #i
    #     lanes = ld.detect(frame)
    #
    #     if predicted is not None:
    #         cv2.line(frame, (predicted[0][0], predicted[0][1]), (predicted[0][2], predicted[0][3]), (0, 0, 255), 5)
    #         cv2.line(frame, (predicted[1][0], predicted[1][1]), (predicted[1][2], predicted[1][3]), (0, 0, 255), 5)
    #
    #     lt.update(lanes)
    #
    #     cv2.imshow('', frame)
    #     if cv2.waitKey(1) & 0xFF == ord('q'):
    #         break

    vid_output_repr='IIT_lanes_filtered_repr.mp4'
    vid_output='IIT_lanes_filtered.mp4'

    # Location of the input video
    clip1=VideoFileClip(args.videopath)
    vid_clip=clip1.fl_image(track)
    vid_clip.write_videofile(vid_output_repr, audio=False)

    # global lines1, lines2
    # json1 = json.dumps(lines1)
    # f = open("lines1.json","w")
    # f.write(json1)
    # f.close()
    # json2 = json.dumps(lines2)
    # f = open("lines2.json","w")
    # f.write(json2)
    # f.close()

    clip2=VideoFileClip('/home/quantumcoder/car-project/test-car-data/vid1.mp4')
    vid_clip=clip2.fl_image(draw)
    vid_clip.write_videofile(vid_output, audio=False)





if __name__ == '__main__':
    main()
