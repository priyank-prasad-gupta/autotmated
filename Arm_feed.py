"""
Created on Thu Dec 12 21:13:30 2019

@author: jankit,ppgupta
"""

import serial  
import cv2
import numpy as np
import imutils



arduino = serial.Serial('COM8',9600)
image_hsv = None
frame=None
pixel = (20,60,80)

# some stupid default

# mouse callback function
def pick_color(event,x,y,flags,param):
    if event == cv2.EVENT_LBUTTONDOWN:
        pixel = image_hsv[y,x]

        #adjust the ranges(+-10, etc):
        upper =  np.array([pixel[0] + 10, pixel[1] + 10, pixel[2] + 40])
        lower =  np.array([pixel[0] - 10, pixel[1] - 10, pixel[2] - 40])
        print(pixel, lower, upper)

      
        # cv2.imshow("mask",image_mask)
        mask= cv2.inRange(image_hsv,lower,upper)   
        #creating a mask using hsv frame with required upper and lower limit.
        cnts = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        
        #storing the list of contours using mask,method,approximation method
        #used grabing all the contour --- contours are closed enclosure of any object..
        
        cnts = imutils.grab_contours(cnts)
        x=0
        y=0
        z=0
        for c in cnts: #reading the contour from the list of contour
            
            area = cv2.contourArea(c)
            
            if area>2:
                
                cv2.drawContours(image_hsv,[c],-1,(0,255,0), 3) #drawing the contour the some colour
                
                M = cv2.moments(c) #storing the moment of whole contour in M so the it can used for any particular pixels
                
                cx = int(M["m10"]/M["m00"])  #to find the centroid of contour we divide the moment at 10 and 01 with Moment 00 #  
                cy = int(M["m01"]/M["m00"])
               
                x=x+cx
                y=y+cy
                z=z+1
                
        # Taking the mean of all possible centroid         
        x=int(x/z)
        y=int(y/z)   
        z1=str(x)+' '+str(y)+' '    # concatenate input for better communication
        
        
       
        print(x,y)
        cv2.circle(frame,(x,y),7,(0,255,255),-1) #drawing a small circle ar the centroid
        cv2.putText(frame, "Centre", (x-20, y-20), cv2.FONT_HERSHEY_SIMPLEX,0.5, (0,255,0), 1)
            
        cv2.imshow("frame",frame)  
      
        #cv2.destroyWindow("frame")
        
        
        # print("area is ...",area)
        
        print("encode:",z1,len(z1))
        
            
        if(x!=744):
          m=abs(1045-y)/(744-x)
    
        #m1=90/57.32; #testing purpose calculation like finding tan inverse 
        
        #con = abs((m-m1)/(1+(m1*m)));
        
        angle =(np.arctan(m) )* 57.32;
        print(angle)
        arduino.write(z1.encode('utf-8')) 
        
       
        

def main():
    
    global image_hsv, pixel,frame # so we can use it in mouse callback
    
    url = 'http://192.168.43.1:8080/video' # IP address of your ipcam or(mobile ip cam)... download it from playstore
    cap = cv2.VideoCapture(url)
   
    cap.set(3,360)
    cap.set(4,240)
    
  
    while(True):
        ret, frame = cap.read()
        if frame is not None:
            cv2.circle(frame,(744,1045),15,(0,255,255),-1)
            cv2.circle(frame,(744,510),9,(0,255,255),-1)
            
            cv2.imshow("bgr",frame)
            cv2.namedWindow('hsv')
            cv2.setMouseCallback('bgr', pick_color)
            
            image_hsv = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
            cv2.imshow("hsv",image_hsv)
            q = cv2.waitKey(1)
            if q == ord("q"):
                break
 
    


    cv2.waitKey(20)
    cv2.destroyAllWindows()

if __name__=='__main__':
    main()
