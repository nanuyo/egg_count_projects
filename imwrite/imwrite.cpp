#include <vector>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void createAlphaMat(Mat &mat)
{
    for (int i = 0; i < mat.rows; ++i) {
        for (int j = 0; j < mat.cols; ++j) {
            Vec4b& rgba = mat.at<Vec4b>(i, j);
            rgba[0] = UCHAR_MAX;
            rgba[1] = saturate_cast<uchar>((float (mat.cols - j)) / ((float)mat.cols) * UCHAR_MAX);
            rgba[2] = saturate_cast<uchar>((float (mat.rows - i)) / ((float)mat.rows) * UCHAR_MAX);
            rgba[3] = saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));
        }
    }
}

/*

void imageWrite(const cv::Mat &image, const std::string filename)
{
    // Support for writing JPG
    vector<int> compression_params;
    compression_params.push_back( CV_IMWRITE_JPEG_QUALITY );
    compression_params.push_back( 100 );

    // This writes to the specified path
    std::string path = "/path/you/provide/" + filename + ".jpg";

    cv::imwrite(path, image, compression_params);
}
*/
int main(int argv, char **argc)
{
    VideoCapture capture(0); // capture video from webcam

    // Create mat with alpha channel
    Mat src, mat(480, 640, CV_8UC4);
    //createAlphaMat(mat);

    for(int i = 0 ; i <100 ; i++)
    capture >> src;

    vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_JPEG_QUALITY/*CV_IMWRITE_PNG_COMPRESSION*/);
    compression_params.push_back(100/*9*/);

    imwrite("alpha.jpg", src/*mat*/, compression_params);

    fprintf(stdout, "Saved JPG file with alpha data.\n");

    capture.release();

    return 0;
}
