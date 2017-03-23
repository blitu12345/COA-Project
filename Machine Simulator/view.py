import numpy as np
import cv2
import sys

strarg=sys.argv[1]+".jpeg"
print strarg

img=cv2.imread(str(strarg),1)
cv2.imshow("img",img)
cv2.waitKey(0)
cv2.destroyAllWindows()