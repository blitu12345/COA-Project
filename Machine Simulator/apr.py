import cv2
import numpy as np


while(1):
    mi=1
    cap = cv2.VideoCapture(0)
    
    while(mi==1):
    
        _, frame = cap.read()
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        
        h, s, v = cv2.split(hsv)
        #print h,s,v
        v=v+255
        h=h+255
        v=v+255
        #print h,s,v
        final_hsv = cv2.merge((h, s, v))
		
        frame = cv2.cvtColor(final_hsv, cv2.COLOR_HSV2BGR)
        cv2.imshow('frame',frame)
        k = cv2.waitKey(10) & 0xFF
        if k == 27:
            break

cv2.destroyAllWindows()



#img = cv2.imread('test.jpg') #load rgb image
# hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV) #convert it to hsv

# h, s, v = cv2.split(hsv)
# v += 255
# final_hsv = cv2.merge((h, s, v))

# img = cv2.cvtColor(final_hsv, cv2.COLOR_HSV2BGR)
# cv2.imwrite("image_processed.jpg", img)
# #img = cv2.imread('input.jpg', 0)

# equalize the histogram of the input image
#histeq = cv2.equalizeHist(img)

#cv2.imshow('Input', img)
#cv2.imshow('Histogram equalized', histeq)
#cv2.waitKey(0)