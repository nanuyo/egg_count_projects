/**
 * @file HoughCircle_Demo.cpp
 * @brief Demo code for Hough Transform
 * @author OpenCV team
 */

//#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/highgui.hpp"
//#include "opencv2/imgproc.hpp"

#include <iostream>



#define MAX_RETRY 10
#define MAX_SKIP_FRAME 5
//#define MAX_EGGS 30

using namespace std;
using namespace cv;

int eggcount = 0, maxeggcount=0;
int retrycnt =0;
//int numOfEggs[MAX_EGGS];
 //int maxcnt;

string intToString(int number){


	std::stringstream ss;
	ss << number;
	return ss.str();
}

namespace
{
    // windows and trackbars name
    const std::string windowName = "Hough Circle Detection Demo";
    const std::string cannyThresholdTrackbarName = "Canny threshold";
    const std::string accumulatorThresholdTrackbarName = "Accumulator Threshold";
    const std::string usage = "Usage : tutorial_HoughCircle_Demo <path_to_input_image>\n";

    // initial and max values of the parameters of interests.
    const int cannyThresholdInitialValue = 75;//100;
    const int accumulatorThresholdInitialValue = 50;
    const int maxAccumulatorThreshold = 200;
    const int maxCannyThreshold = 255;
    


    int HoughDetection(const Mat& src_gray, const Mat& src_display, int cannyThreshold, int accumulatorThreshold)
    {
        // will hold the results of the detection
        std::vector<Vec3f> circles;
        char key;
 
        eggcount = 0;

        // runs the actual detection
        HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows/8, cannyThreshold, accumulatorThreshold, 0, 0 );

        // clone the colour, input image for displaying purposes
//        Mat display = src_display.clone();
        for( size_t i = 0; i < circles.size(); i++ )
        {
  //          Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
#if 0   // circle center
            circle( display, center, 3, Scalar(0,255,0), -1, 8, 0 );
            // circle outline
            circle( display, center, radius, Scalar(0,0,255), 3, 8, 0 );

            putText(display, intToString(radius),center,1,1,Scalar(0,255,0),2);
#endif
            if (radius >= 55 && radius <= 65 )
            {
            	eggcount ++;
            }

        }
#if 0
 putText(display, "Eggs:" + intToString(eggcount),Point(10,50),2,2,Scalar(255,0,0),2);
#else
     //   numOfEggs[eggcount]++;

       if(eggcount > maxeggcount)
        	maxeggcount = eggcount;
/*
        putText(display, "Eggs:" + intToString(maxeggcount),Point(10,50),2,2,Scalar(255,0,0),2);
*/
        retrycnt ++;
        if(retrycnt >= MAX_RETRY)
        {
#if 0              
  maxcnt = 0;
                for (int kk =0 ; kk < (MAX_EGGS) ; kk++)
		{
		   if (maxcnt <  numOfEggs[kk])
		  {

maxcnt =  numOfEggs[kk] ;                       
maxeggcount = kk;
cout << "maxcnt:" << maxcnt << "maxeggcount:" << maxeggcount <<  endl;

		  }
		}
#endif
//putText(display, "Eggs:" + intToString(maxeggcount),Point(10,50),2,2,Scalar(255,0,0),2);
                cout << maxeggcount ;
  //imshow( windowName, display);
        	retrycnt = 0;
        	maxeggcount = 0;
        	
 
        }

        
#endif
        // shows the results
      //  imshow( windowName, display);

        return eggcount;
    }
}


int main(int argc, char** argv)
{
    Mat src, src_gray;
    int maxeggcnt = 0, eggcnt=0;
    char key;

    cout << "test";

   VideoCapture capture(0); // capture video from webcam
key= waitKey(1000);

    //declare and initialize both parameters that are subjects to change
       int cannyThreshold = cannyThresholdInitialValue;
       int accumulatorThreshold = accumulatorThresholdInitialValue;

       // create the main window, and attach the trackbars
 //      namedWindow( windowName, WINDOW_AUTOSIZE );
   //    createTrackbar(cannyThresholdTrackbarName, windowName, &cannyThreshold,maxCannyThreshold);
     //  createTrackbar(accumulatorThresholdTrackbarName, windowName, &accumulatorThreshold, maxAccumulatorThreshold);

    while( true )
    {
       for(int k = 0 ; k < MAX_SKIP_FRAME ; k++)
           capture >> src;
  
     /*  for(int j=0; j < MAX_EGGS ; j++)
            numOfEggs[j] = 0;
*/
  	for(int i = 0 ; i < MAX_RETRY ; i ++)
    	{
        // Capture the current frame from the input video stream
        capture >> src;
       

    // Convert it to gray
    cvtColor( src, src_gray, COLOR_BGR2GRAY );

    // Reduce the noise so we avoid false circle detection
    GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );



    
        cannyThreshold = std::max(cannyThreshold, 1);
        accumulatorThreshold = std::max(accumulatorThreshold, 1);

        //runs the detection, and update the display
        eggcnt = HoughDetection(src_gray, src, cannyThreshold, accumulatorThreshold);

    	}


       maxeggcount = 0;

 
        key= waitKey(0);

        if( key == 27 )  break;

    }

   capture.release();

    return 0;
}
