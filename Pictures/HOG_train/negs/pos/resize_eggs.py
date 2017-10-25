import os
import cv2

pic_num = 1
    
if not os.path.exists('pos'):
       os.makedirs('pos')
        
for i in 1,2,3,4 :
	img = cv2.imread(str(i)+".jpg")
	resized_image = cv2.resize(img, (100, 150))
	cv2.imwrite("pos/"+str(i)+".jpg",resized_image)

            

