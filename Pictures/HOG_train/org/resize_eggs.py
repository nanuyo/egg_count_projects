import os
import cv2

pic_num = 1
    
if not os.path.exists('pos'):
       os.makedirs('pos')
        
for i in 1,2,3,4 :
	img = cv2.imread("eggcut"+str(i)+".jpg")
	resized_image = cv2.resize(img, (64, 64))
	cv2.imwrite("pos/"+"eggcut"+str(i)+".jpg",resized_image)

            

