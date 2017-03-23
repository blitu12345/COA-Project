import cv2
import sys
while(1):
    mi=1
    cap = cv2.VideoCapture(0)
    
    while(mi==1):
    
        _, frame = cap.read()
        cv2.imshow('frame',frame)
        k = cv2.waitKey(10) & 0xFF
        if k == 27:
            break

cv2.destroyAllWindows()