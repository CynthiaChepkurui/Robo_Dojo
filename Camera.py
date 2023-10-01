import supervision as sv
from ultralytics import YOLO
import cv2
import numpy as np
import time


vid = cv2.VideoCapture(0)
vid.set(cv2.CAP_PROP_FRAME_WIDTH, 1280)
vid.set(cv2.CAP_PROP_FRAME_HEIGHT, 1024)
time.sleep(2)
vid.set(cv2.CAP_PROP_EXPOSURE, -8.0)


#functions needed
#fumction to bound boxes
def image_inference(frame):

    #load YOLO
    model = YOLO('best.pt')

    #detect 
    results = model.predict(frame)

    # Annotate the frame with bounding boxes and labels
    box_label(image, box, label='', color=(128, 128, 128), txt_color=(255, 255, 255))


    result = results[0]
    box = results.boxes[0]

    #initialize box properties
    for box in results.boxes:
        coordinates= box.xyxy[0].tolist()
        coordinates = [round(x) for x in cords]
        label = result.names[box.cls[0].item()]
        confidence = round(box.conf[0].item(), 2)

    #arm control acccording to OD
    for box in results:
        if label == 'redwheel' and confidence >= 0.7:
            #arm control
        elif label == 'bluewheel' and confidence >= 0.7:
            #arm control
        elif label == 'whitewheel' and confidence >= 0.7:
            #arm control  
        elif label == 'trailer' and confidence >= 0.7:
            #arm control
        elif label == 'cabin' and confidence >= 0.7:
            #arm control  
        elif label == 'engine' and confidence >= 0.7:
            #arm control

#https://inside-machinelearning.com/en/yolov8-how-to-use/
#flexibility in adjusting the appearance of bounding boxes and labels
def box_label(image, box, label='', color=(128, 128, 128), txt_color=(255, 255, 255)):
    lw = max(round(sum(image.shape) / 2 * 0.003), 2)
    p1, p2 = (int(box[0]), int(box[1])), (int(box[2]), int(box[3]))
    cv2.rectangle(image, p1, p2, color, thickness=lw, lineType=cv2.LINE_AA)
    if label:
        tf = max(lw - 1, 1)  # font thickness
        w, h = cv2.getTextSize(label, 0, fontScale=lw / 3, thickness=tf)[0]  # text width, height
        outside = p1[1] - h >= 3
        p2 = p1[0] + w, p1[1] - h - 3 if outside else p1[1] + h + 3
        cv2.rectangle(image, p1, p2, color, -1, cv2.LINE_AA)  # filled
        cv2.putText(image, label, (p1[0], p1[1] - 2 if outside else p1[1] + h + 2), 0,
                    lw / 3, txt_color, thickness=tf, lineType=cv2.LINE_AA)


while True:
  ret, frame = vid.read()

  height, width = frame.shape[:2]   
  # function for prediction and run inference
  image_inference(frame)

  # Break the loop if 'q' is pressed (will remove it since the robot doesn't need it)
  if cv2.waitKey(1) & 0xFF == ord('q'):
      break
   
vid.release()
cv.destroyAllWindows()  
