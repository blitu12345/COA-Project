import cv2, numpy
import sys
from matplotlib import pyplot as plt
x=0
y=0
z=int(sys.argv[1])*20
while(1):
	mi=1
	cap = cv2.VideoCapture(0)
	
	
	while(mi==1):
    # Take each frame
		
		_, frame = cap.read()
			
		frame = frame[0+z:1000-z, 0+z:1000-z]
		#cv2.namedWindow("output", cv2.WINDOW_NORMAL)        # Create window with freedom of dimensions
		frame = cv2.resize(frame,None,fx=1.5, fy=1.5, interpolation = cv2.INTER_CUBIC)
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
			cv2.imwrite("2.jpeg",frame)
		""""if(a==49):
			frame = frame[0:1000, 0:1000]
		if(a==50):
			frame=frame[80:920,80:920]
		if(a==51):
			frame=frame[120:880,120:880]
		if(a==52):
			frame=frame[160:840,160:840]
		if(a==53):
			frame=frame[200:800,200:800]
		if(a==54):
			frame=frame[240:760,240:760]
		if(a==55):
			frame=frame[280:720,280:720]
		if(a==56):
			frame=frame[320:680,320:680]
		if(a==57):
			frame=frame[360:640,360:640]"""
		#if a!=255:
		#	frame = cv2.resize(frame,None,fx=2, fy=2, interpolation = cv2.INTER_CUBIC)
		cv2.circle(frame,(250+x,150+y), 63, (0,140,0), 1)
		cv2.imshow('frame',frame)
		k = cv2.waitKey(10) & 0xFF
   		if k == 27:
			break

cv2.destroyAllWindows()

"""img = cv2.imread("2.jpeg")
crop_img = img[100:400, 100:500] # Crop from x, y, w, h -> 100, 200, 300, 400
# NOTE: its img[y: y + h, x: x + w] and *not* img[x: x + w, y: y + h]
cv2.imshow("cropped", crop_img)
cv2.waitKey(0)"""