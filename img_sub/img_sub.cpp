/*
 * img_sub.cpp
 *
 *  Created on: Sep 6, 2017
 *      Author: hjpark
 */




//opencv
#include <opencv2/opencv.hpp>
//C
#include <stdio.h>
//C++
#include <iostream>
#include <sstream>

using namespace cv;
using namespace std;
Ptr<BackgroundSubtractor> pMOG2; //MOG2 Background subtractor
int g_thresh = 40;
Mat dst, bin;
Mat Foreground;

//int to string helper function
string intToString(int number){

    //this function has a number input and string output
    std::stringstream ss;
    ss << number;
    return ss.str();
}

void on_trackbar( int, void* )
{
  threshold( dst, bin, g_thresh, 255, THRESH_BINARY );

  vector< vector< cv::Point> > contours;
  vector<Vec4i> hierarchy;
  double area1, cnt=0;
  Rect bounding_rect;
  bool objectDetected = false;
  int theObject[2] = {0,0};

 // findContours(bin, contours, noArray(),RETR_LIST,CHAIN_APPROX_SIMPLE  );
 findContours(bin,contours, hierarchy,CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE ); // finds contours on bin image
 //putText(bin,"Contours1 :"+intToString(contours.size()) ,Point(100,100),1,1,Scalar(255,0,0),2);
 cout << "Contours1: " << contours.size() << "\n";
 // bin = Scalar::all(0);
  Scalar color( 255,255,255 );

  for( int i = 0; i< contours.size(); i++ ) // iterate through each contour.
  {
	  area1 = contourArea(contours[i],false);
	  if(area1 > 100)
	  {
		  cnt++;
		  objectDetected = true;
		  // drawContours( bin, contours, -1, Scalar::all(255));
		  drawContours( bin, contours, i , color, CV_FILLED, 8, hierarchy );
		  //write the position of the object to the screen
		 // putText(bin,"Egg"+intToString(cnt) + " " + intToString(area1) ,Point(100,100+ cnt*20),1,1,Scalar(255,0,0),2);
		  bounding_rect=boundingRect(contours[i]); //Bound and Draw rectangle each object which detected at the end on src(original image)
		  rectangle(Foreground, bounding_rect,  Scalar(0,255,0),3, 8,0);
		  int x = bounding_rect.x+bounding_rect.width/2;
          int y = bounding_rect.y+bounding_rect.height/2;
		  putText(Foreground,"Egg" + intToString(cnt),Point(x,y),1,1,Scalar(255,0,0),2);
	  }
  }

  imshow( "Binary", bin );
  imshow("Foreground", Foreground);

}

int main(int argc, char* argv[])
{
	char key;
	Mat grayImage1,grayImage2, thresholdImage;

	Mat fgMaskMOG2; //fg mask fg mask generated by MOG2 method

	 //create GUI windows
    namedWindow("Backgroud");
	namedWindow("Foreground");
	namedWindow("Mask");
	namedWindow("DST");
	namedWindow("thresholdImage");



	  //create Background Subtractor objects
	//pMOG2 = createBackgroundSubtractorMOG2(); //MOG2 approach
	//Mat Backgroud = imread("/home/hjpark/Pictures/pic2.jpg");
	//Mat Backgroud = imread("../../Pictures/BlackBack01.jpg");
Mat Backgroud = imread("../../Pictures/back_egg.jpg");
	//Mat Backgroud = imread("/home/hjpark/Pictures/ref4eggsb.jpg");

    if( Backgroud.empty() )                      // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    cvtColor(Backgroud,grayImage1,COLOR_BGR2GRAY);

    // Foreground = imread("/home/hjpark/Pictures/pic1.jpg");
     //Foreground = imread("../../Pictures/eggsAsetBlack08.jpg");
 Foreground = imread("../../Pictures/front_egg.jpg");
    // Foreground = imread("../../Pictures/eggsAsetBlack01.jpg");
    // Foreground = imread("/home/hjpark/Pictures/ref4eggs2.jpg");

    if( Foreground.empty() )                      // Check for invalid input
       {
           cout <<  "Could not open or find the image" << std::endl ;
           return -1;
       }
    cvtColor(Foreground,grayImage2,COLOR_BGR2GRAY);

	//resize(Backgroud, Backgroud, cv::Size(Backgroud.cols * 0.5,Backgroud.rows * 0.5), 0, 0, CV_INTER_LINEAR);
	//resize(Foreground, Foreground, cv::Size(Foreground.cols * 0.5,Foreground.rows * 0.5), 0, 0, CV_INTER_LINEAR);




	imshow("Backgroud", Backgroud);
	imshow("Foreground", Foreground);


	//update the background model
	//pMOG2->apply( Backgroud, fgMaskMOG2);
	//update the background model
	//pMOG2->apply( Foreground, fgMaskMOG2);
	//fgMaskMOG2 =  Foreground - Backgroud;
//fgMaskMOG2 =  Backgroud - Foreground;
//absdiff(Backgroud,Foreground,fgMaskMOG2);
absdiff(grayImage1,grayImage2,fgMaskMOG2);
//	subtract(Backgroud,Foreground,fgMaskMOG2);

	imshow("Mask", fgMaskMOG2);
	/*vector<int> compression_params;
	    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	    compression_params.push_back(9);
	imwrite("egggg.jpg", fgMaskMOG2, compression_params );
*/

	//cvtColor(fgMaskMOG2,dst,CV_BGR2GRAY);  // converts image from rgb(src) to gray level (dst)
	//threshold(dst,bin,g_thresh,255,THRESH_BINARY); // Tresholds image with level = 40 from gray level(dst) to binary (bin)
	//findContours(bin,contours, hierarchy,CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE ); // finds contours on bin image
	threshold(fgMaskMOG2,thresholdImage,SENSITIVITY_VALUE,255,THRESH_BINARY);
	imshow("thresholdImage", thresholdImage);
	//imshow("Binary", bin);

	createTrackbar("Threshold", "thresholdImage",
		    &g_thresh,
		    255,
		    on_trackbar
		  );
		  on_trackbar(0, 0);

	do
	{
	 key= waitKey(0);
	}while(key != 27);

}
