import cv2
import numpy as np
from matplotlib import pyplot as plt
 
img = cv2.imread('1.jpeg')
 
blur = cv2.GaussianBlur(img,(5,5),0)
cv2.imshow("img",blur)
cv2.waitKey(0)
cv2.destroyAllWindows()
 
"""plt.subplot(121),plt.imshow(img),plt.title('Original')
plt.xticks([]), plt.yticks([])
plt.subplot(122),plt.imshow(blur),plt.title('Blurred')
plt.xticks([]), plt.yticks([])
plt.show()"""
