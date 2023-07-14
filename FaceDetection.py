import cv2 # import openCV

#I defined the algorithm using the haarcascade

alg = 'indexAlgorithmV2.xml'  # accessed the model file

cascade = cv2.CascadeClassifier(alg) # loading the model with cv2
cam = cv2.VideoCapture(0) # initialization camera

while True:
    _,img = cam.read() # read the frame from the camera
    
    grayImg = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY) 
    face = cascade.detectMultiScale(grayImg) 

    for (x, y, w, h) in face: 
        cv2.rectangle(img, (x, y), (x + w, y + h),(0,255,0),2) 
    cv2.imshow("FaceDetect",img)

    key = cv2.waitKey(1)

    if key == 81 or key == 113 :
        break

cam.release()
cv2.destroyAllWindows()