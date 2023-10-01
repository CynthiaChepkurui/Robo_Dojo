import supervision as sv
from ultralytics import YOLO
import cv2
import numpy as np
import time


vid = cv2.VideoCapture(0)
vid.set(cv2.CAP_PROP_FRAME_WIDTH, 500)
vid.set(cv2.CAP_PROP_FRAME_HEIGHT, 500)
time.sleep(2)
vid.set(cv2.CAP_PROP_EXPOSURE, -8.0)


#functions needed
#function to bound boxes
def image_inference(frame):

    #load YOLO
    model = YOLO('best.pt')

    #detect 
    results = model.predict(frame)

    # Annotate the frame with bounding boxes and labels
    box_label(image, box, label='', color=(128, 128, 128), txt_color=(255, 255, 255))


    result = results[0]
    box = results.boxes[0]
    # Initialize a list to keep track of labels to ignore
    labels_to_ignore = []

# Initialize box properties
for box in results.boxes:
    #initialize variables to readable format from pytorch
    coordinates = box.xyxy[0].tolist()
    coordinates = [round(x) for x in coordinates]
    label = result.names[box.cls[0].item()]
    confidence = round(box.conf[0].item(), 2)

    # Arm control according to OD
    if label == 'redwheel' and confidence >= 0.7:
        print('Performing arm control for redwheel')
        # Arm control code for redwheel
        labels_to_ignore.append('redwheel')
    elif label == 'bluewheel' and confidence >= 0.7:
        print('Performing arm control for bluewheel')
        # Arm control code for bluewheel
    elif label == 'whitewheel' and confidence >= 0.7:
        print('Performing arm control for whitewheel')
        # Arm control code for whitewheel
    elif label == 'trailer' and confidence >= 0.7:
        print('Performing arm control for trailer')
        # Arm control code for trailer
    elif label == 'cabin' and confidence >= 0.7:
        print('Performing arm control for cabin')
        # Arm control code for cabin
    elif label == 'engine' and confidence >= 0.7:
        print('Performing arm control for engine')
        # Arm control code for engine


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
