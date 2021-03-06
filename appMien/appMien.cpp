// appMien.cpp

#include "Mien/Mien.hpp"
#include "MienDL/MienDL.hpp"
#include "Mien58/Mien58.hpp"
#include "MienNN/MienNN.hpp"

#include "MienSW/MienSW.hpp"
#include "MienST/MienST.hpp"

#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;
#pragma comment(lib,"opencv_world341.lib")

#include <dlib/opencv.h>
#include <dlib/gui_widgets.h>

//#include "facedetect-dll.h"
//#pragma comment(lib,"libfacedetect-x64.lib")
//#define DETECT_BUFFER_SIZE 0x20000
 
int argc = 2;
char* argv[] = {
	(char*)"appMien.exe",
	(char*)"/Users/zhongsifen/Work/Data/Face/th9MS3IXBW.jpg",
};

int main(int _argc, char* _argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <image_file_name>\n", argv[0]);
		return -1;
	}
	Mien::Image image = imread(argv[1]);	if (image.empty()) return -1;

	//Mien58 mien58;
	//mien58.setup(image.rows*4, image.cols*4);
	//MienDL* mien_dl = mien58.getMienDL();
	//MienFD* mien_fd = mien58.getMienFD();
	//MienNN* mien_nn = mien58.getMienNN();

	MienST* mien_st = new MienST;
	//MienSW* mien_sw = new MienSW;

	Mien::Gray gray;
	Mien::toGray(image, gray);

	Mien::Face face;
	Mien::Landmark landmark;
	Mien::EEM eem;
	//mien_fd->doFace(gray, face);
	//mien_fd->doLandmark(gray, face, landmark);
	//mien_fd->doEem(landmark, eem);


	mien_st->doFace(gray, face);
	mien_st->doLandmark(gray, landmark);

	//mien_sw->doFace(image, face);
	//mien_sw->doLandmark(image, face, landmark);

	Mat w = image.clone();
	Mien::showFace(w, face);
	Mien::showLandmark(w, landmark);
	cv::imshow("w", w);	cv::waitKey();

	return 0;

	Mien::EEM tri;
	cv::Size box;
	//mien58.getTri(tri, box);
	Mien::Chip chip;
	Mien::toChipTri(image, landmark, tri, box, chip);

	Mat u = chip.clone();
	cv::imshow("u", u);	cv::waitKey();

	return 0;

	//mien_fd->doChip(image, face, chip);

	Mien::showFace(u, face);
	Mien::showEEM(u, eem);
	//mien_fd->toGray(chip, gray);
	//mien_fd->doLandmark(gray, face, landmark);
	//mien_fd->doEEM(landmark, eem);
	//mien_fd->showFace(u, face);
	//mien_fd->showEEM(u, eem);
	cv::imshow("u", u);	cv::waitKey();

	return 0;
}

