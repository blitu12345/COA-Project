import sys
import cv2
import time

a=int(sys.argv[1])

#cv2.waitKey(a)

cap = cv2.VideoCapture(0) # video capture source camera (Here webcam of laptop) 
time.sleep(a)
ret,frame = cap.read() # return a single frame in variable `frame`

while(True):
    cv2.imshow('img1',frame) #display the captured image
     
    cv2.imwrite("13.jpeg",frame)
    
    cv2.destroyAllWindows()
    break

cap.release()