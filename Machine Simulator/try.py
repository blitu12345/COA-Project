import numpy as np
import cv2
from matplotlib import pyplot as plt
import sys
x=0
y=0
xi=int(sys.argv[1])*35
yi=int(sys.argv[2])*25
ri=int(sys.argv[3])*6
while(1):
    mi=1
    cap = cv2.VideoCapture(0)
    
    while(mi==1):
    # Take each frame
    
        _, frame = cap.read()
        #_, frame1 =cap.read()
        a = cv2.waitKey(10) & 0xFF
        if(a==119):
            y=y-10
        if(a==115):
            y=y+10
        if(a==97):
            x=x-20
        if(a==100):
            x=x+20
        if(a==99):
            cv2.imwrite("1.jpeg",frame)
        #print a
        cv2.circle(frame,(xi+x,yi+y), ri, (0,140,0), 1)
        cv2.imshow('frame',frame)
        k = cv2.waitKey(10) & 0xFF
        if k == 27:
            break

cv2.destroyAllWindows()