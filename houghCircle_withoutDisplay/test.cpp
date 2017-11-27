#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

// initial and max values of the parameters of interests.
const int cannyThresholdInitialValue = 85;//75, 100;
const int accumulatorThresholdInitialValue = 40;//50;


int HoughDetection(const Mat& src_gray, const Mat& src_display, int cannyThreshold, int accumulatorThreshold)
{
	// will hold the results of the detection
    std::vector<Vec3f> circles;
    int eggcount = 0;

    // runs the actual detection
    HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows/8, cannyThreshold, accumulatorThreshold, 0, 0 );

    for( size_t i = 0; i < circles.size(); i++ )
    {
    	int radius = cvRound(circles[i][2]);
    	//if (radius >= 55 && radius <= 65 )
        {
          	eggcount ++;
        }

    }

    cout <<  "Eggs: " << eggcount << "\n";

    return eggcount;
}

int main(void)
{
	Mat src, src_gray;
	char key;

	cout << "test\n" ;
	VideoCapture capture(0); // capture video from webcam

	while( true )
    {
		capture >> src;
        // Convert it to gray
		cvtColor( src, src_gray, COLOR_BGR2GRAY );
		// Reduce the noise so we avoid false circle detection
		GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );

		HoughDetection(src_gray, src, cannyThresholdInitialValue, accumulatorThresholdInitialValue);
		//key= waitKey(10);
		//if( key == 27 )  break;
    }

	capture.release();

	return 0;
}
