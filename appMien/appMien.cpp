// appMien.cpp

//#include "MienFD/MienFD.hpp"
#include "MienDL/MienDL.hpp"

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
	Mat w = image.clone();
	if (image.empty())
	{
		fprintf(stderr, "Can not load the image file %s.\n", argv[1]);
		return -1;
	}
	MienType::Gray gray;
	cvtColor(image, gray, CV_BGR2GRAY);

	MienDL mien;
	MienType::Face face;
	MienType::Landmark landmark;
	MienType::Chip chip;

	mien.face(gray, face);
	mien.landmark(gray, face, landmark);

	mien.showFace(w, face);
	mien.showLandmark(w, landmark);
	cv::imshow("w", w);	cv::waitKey();

	mien.chip(image, face, chip);
	cv::imshow("chip", chip);	cv::waitKey();

#if 0
	cv::Rect face;
	std::vector<cv::Point> landmark;
	std::vector<cv::Point2f> eem;
	bool ret = false;
	ret = mien.detect(gray, face, landmark);	if (!ret) return -1;
	ret = mien.eem(landmark, eem);

	Mat w = image.clone();
	mien.showFace(w, face);
	mien.showLandmark(w, landmark);
	mien.showEEM(w, eem);
	cv::imshow("w", w);	cv::waitKey();


	dlib::matrix<dlib::rgb_pixel> chip_d;
	dlib::matrix<float, 0, 1> desc_d;

	MienType::Chip chip;
	MienType::Desc_D desc;

	mien.desc(image, chip, desc);
	//mien.desc(image, desc);
	cv::imshow("w", chip);	cv::waitKey();
	cv::imshow("x", chip);	cv::waitKey();
#endif

	return 0;
}
