import sys
import string
import numpy as np
import cv2 as cv


file = open('D:/JPEGImages/data.txt','r')

for line in file.readlines():
        s=line.strip().lstrip('[').rstrip(']')
        b=s.split(',')
        l = []
        for j in b:
                l.append(np.uint8(j))
        img = np.ndarray(shape=(512,512), dtype=np.uint8, buffer=np.array(l), offset=0, order="C")
        cv.imshow("1",img)
        cv.waitKey();

    


    
