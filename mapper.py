#!/usr/bin/env python3

import sys
import cv2 as cv
import numpy as np
import os

#file = open('/home/hadoop/workspace/data.txt','r')
#for line in file.readlines():

for line in sys.stdin:

    s=line.strip().lstrip('[').rstrip(']')
    b=s.split(',')
    l = []
    for j in b:
        l.append(np.uint8(j))
    img = np.ndarray(shape=(512,512), dtype=np.uint8, buffer=np.array(l), offset=0, order="C")
    
    face = cv.imread('/home/hadoop/workspace/target.jpg',cv.IMREAD_GRAYSCALE)
    
    sift=cv.xfeatures2d.SIFT_create()
    kp1, des1 = sift.detectAndCompute(img, None)
    kp2, des2 = sift.detectAndCompute(face, None) 
    
    bf = cv.BFMatcher()
    matches = bf.knnMatch(des1, des2, k=2) 
    
    good = [] 
    for m,n in matches:
        if m.distance<0.5*n.distance:
            good.append([m])

    if(len(good)>20):
        img2 = cv.drawMatchesKnn(img, kp1, face, kp2, good, None, flags=2) 
#        cv.imshow('Match!',img2)
#        cv.waitKey()
        os.system('echo yes')
        print('%s\t%s'%('s','1'))



            
