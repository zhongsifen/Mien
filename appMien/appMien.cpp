// appMien.cpp

#include "Mien/Mien.hpp"
#include "MienDL/MienDL.hpp"
#include "Mien58/Mien58.hpp"

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

	Mien58 mien58;

	mien58.setup();

	Mat image = imread(argv[1]);		if (image.empty()) return -1;
	cv::namedWindow("w");
	Mat w = image.clone();

	cv::imshow("w", w);	cv::waitKey();

	return 0;
}

#if 0
int main_(int _argc, char* _argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <image_file_name>\n", argv[0]);
		return -1;
	}

	cv::namedWindow("w");

	Mat image = imread(argv[1]);		if (image.empty()) return -1;
	Mat w = image.clone();

	cv::imshow("w", w);	cv::waitKey();

	MienType::Gray gray;
	cvtColor(image, gray, CV_BGR2GRAY);

	MienType::EEM tri(3);
	tri[0] = Mien58::_e1;
	tri[1] = Mien58::_e2;
	tri[2] = Mien58::_m;
	cv::Size box = Mien58::_r;

	MienDL mien;
	MienType::Face face;
	MienType::Landmark landmark;
	MienType::EEM eem;
	MienType::Chip chip;
	MienType::Desc desc;

	mien.face(gray, face);
	mien.landmark(gray, face, landmark);
	mien.eem(landmark, eem);
	mien.chip(image, eem, tri, box, chip);

	mien.showFace(w, face);
	//mien.showLandmark(w, landmark);
	mien.showEEM(w, eem);
	cv::imshow("w", w);	cv::waitKey();

	cv::namedWindow("chip");
	cv::imshow("chip", chip);	cv::waitKey();

	//mien.desc(image, face, chip, desc);
	//mien.chip(image, face, chip);
	//cv::imshow("chip", chip);	cv::waitKey();

	image = chip;
	w = image.clone();
	cvtColor(image, gray, CV_BGR2GRAY);
	mien.face(gray, face);
	mien.landmark(gray, face, landmark);
	mien.eem(landmark, eem);
	mien.chip(image, eem, tri, box, chip);

	mien.showFace(w, face);
	//mien.showLandmark(w, landmark);
	mien.showEEM(w, eem);
	cv::imshow("chip", w);	cv::waitKey();

	return 0;
}

#endif