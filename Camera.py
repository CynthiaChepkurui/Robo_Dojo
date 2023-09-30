import cv2
import numpy as np
from ultralytics import YOLO
import supervision as sv
import time

#https://inside-machinelearning.com/en/yolov8-how-to-use/
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

def plot_bboxes(image, boxes, labels=None, colors=None, score=True, conf=None):
    # My_Custom Labels
    if labels is None:
        labels = {
            0: '__background__', 1: 'blue_wheel', 2: 'cabin', 3: 'engine', 4: 'red_wheel',
            5: 'trailer', 6: 'wheel', 7: 'white_wheel'
        }

    # My_Custom Colors
    if colors is None:
        colors = [(0, 0, 255), (255, 255, 255), (0, 0, 255)]  # Red, White, Blue

    for box in boxes:
        # Add score in label if score=True
        if score:
            label = labels.get(int(box[-1]) + 1, 'Unknown') + f" {round(100 * float(box[-2]), 1)}%"
        else:
            label = labels.get(int(box[-1]) + 1, 'Unknown')

        # Filter boxes under the confidence threshold if set
        if conf is None or box[-2] > conf:
            color = colors[int(box[-1])]
            box_label(image, box, label, color)

#perform video inference (import part)
def inference():
    video_info = sv.VideoInfo.from_video_path(vid)

#https://roboflow.com/video-inference/yolov8#:~:text=YOLOv8%20Video%20Inference%3A%20A%20How-To%20Guide%201%201.,target%20video%203%203.%20Process%20the%20target%20video
    # callback that runs inference
    def process_frame(frame: np.ndarray, _) -> np.ndarray:
        results = model(frame, imgsz=1280)[0]
        detections = sv.Detections.from_yolov8(results)

        box_annotator = sv.BoxAnnotator(thickness=4, text_thickness=4, text_scale=2)

        labels = [f"{model.names[class_id]} {confidence:0.2f}" for _, _, confidence, class_id, _ in detections]
        frame = box_annotator.annotate(scene=frame, detections=detections, labels=labels)

        return frame

    sv.process_video(source_path=vid, target_path=f"result.mp4", callback=process_frame)

vid = cv2.VideoCapture(0)
vid.set(cv2.CAP_PROP_FRAME_WIDTH, 1280)
vid.set(cv2.CAP_PROP_FRAME_HEIGHT, 1024)
time.sleep(2)
vid.set(cv2.CAP_PROP_EXPOSURE, -8.0)

while True:
    ret, frame = vid.read()
   
    height, width = frame.shape[:2]   
    # Load the YOLO model 
    model = YOLO('best.pt')

    # Run the YOLO model on the frame to detect objects
    detections = model(frame)[0]

    # Annotate the frame with bounding boxes and labels
    plot_bboxes(frame, detections, labels=None, colors=None, score=True, conf=None)

    # Display the annotated frame
    cv.imshow('frame', frame)

    # Loop through the detected objects and takes actions based on labels
    for box in detections:
        label = labels.get(int(box[-1]) + 1, 'Unknown')
        
        # Perform actions based on the detected label (i think arm design will go here)
        if label == 'blue_wheel':
            # code to pick up the blue wheel goes here
            print("Detected a blue wheel. Picking it up...")

    # Break the loop if 'q' is pressed (will remove it since the robot doesn't need it)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
   
vid.release()
cv.destroyAllWindows()



