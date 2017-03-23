import cv2
import os
import sys
a=sys.argv[1]+".jpeg"
try: 
    os.remove(str(a))
except: pass


