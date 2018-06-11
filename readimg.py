import cv2 as cv
import numpy as np
import os

rootdir ='/home/hadoop/workspace/imgs'
file = open('/home/hadoop/workspace/data.txt','w')
list = os.listdir(rootdir)

index = 1

target = cv.imread('/home/hadoop/workspace/target.jpg',cv.IMREAD_GRAYSCALE)
target = cv.resize(target,(139,175))
file.write('00')
file.write('\t')
file.write(str(target.reshape(1,-1).tolist()[0]))
file.write('\n')

for i in range(0,len(list)):
    path = os.path.join(rootdir,list[i])
    if os.path.isfile(path):
        img = cv.imread(path,cv.IMREAD_GRAYSCALE)
        img = cv.resize(img,(320,240))

        file.write(list[i][:2])
        file.write('\t')
        file.write(str(img.reshape(1,-1).tolist()[0]))
        file.write('\n')

file.close()


