// appMien.cpp

#include "Mien/Mien.hpp"

#include <stdio.h>
#include <opencv2/opencv.hpp>
//#include "facedetect-dll.h"
//#pragma comment(lib,"libfacedetect-x64.lib")
#pragma comment(lib,"opencv_world341.lib")

//define the buffer size. Do not change the size!
#define DETECT_BUFFER_SIZE 0x20000
using namespace cv;
 
int argc = 2;
char* argv[] = {
	(char*)"appMien.exe",
	(char*)"/Users/zhongsifen/Work/Mien58_data/data/mike/132229197802080070.jpg",
};

int main(int _argc, char* _argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <image_file_name>\n", argv[0]);
		return -1;
	}

	//load an image and convert it to gray (single-channel)
	Mat image = imread(argv[1]);
	if (image.empty())
	{
		fprintf(stderr, "Can not load the image file %s.\n", argv[1]);
		return -1;
	}
	Mat gray;
	cvtColor(image, gray, CV_BGR2GRAY);

	Mien mien;
	cv::Rect face;
	std::vector<cv::Point> landmark;
	bool ret = false;
	ret = mien.landmark(gray, face, landmark);	if (!ret) return -1;

	Mat w = image.clone();
	mien.show_face(w, face);
	mien.show_landmark(w, landmark);
	cv::imshow("w", w);	cv::waitKey();

	return 0;
}
