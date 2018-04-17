import cv2 as cv
import numpy as np
import os

rootdir ='D:/JPEGImages'
file = open('D:/JPEGImages/data.txt','w')
list = os.listdir(rootdir)


for i in range(0,len(list)-1):
    path = os.path.join(rootdir,list[i])
    if os.path.isfile(path):
        img = cv.imread(path,cv.IMREAD_GRAYSCALE)
        img = cv.resize(img,(512,512))
        file.write(str(img.reshape(1,-1).tolist()[0]))
        file.write('\n')

file.close()


