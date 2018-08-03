// appMien.cpp

#include "Mien/Mien.hpp"
#include "MienDL/MienDL.hpp"
#include "Mien58/Mien58.hpp"
#include "MienNN/MienNN.hpp"

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
	MienDL::Image image = imread(argv[1]);		if (image.empty()) return -1;

	Mien58 mien58;
	mien58.setup(image.rows*4, image.cols*4);
	MienDL* mien_dl = mien58.getMienDL();
	MienFD* mien_fd = mien58.getMienFD();
	MienNN* mien_nn = mien58.getMienNN();

	Mien::Gray gray;
	Mien::doGray(image, gray);

	Mien::Face face;
	Mien::Landmark landmark;
	Mien::EEM eem;
	//mien_fd->doFace(gray, face);
	//mien_fd->doLandmark(gray, face, landmark);
	//mien_fd->doEem(landmark, eem);
	mien_nn->doEEM(image, face, eem);

	Mat w = image.clone();
	Mien::showFace(w, face);
	Mien::showEEM(w, eem);
	cv::imshow("w", w);	cv::waitKey();

	Mien::EEM tri;
	cv::Size box;
	mien58.getTri(tri, box);
	Mien::Chip chip;
	Mien::doChipTri(image, eem, tri, box, chip);
	//mien_fd->doChip(image, face, chip);
	Mat u = chip.clone();
	cv::imshow("u", u);	cv::waitKey();

	mien_nn->setup(chip.rows, chip.cols);
	mien_nn->doEEM(chip, face, eem);
	Mien::showFace(u, face);
	Mien::showEEM(u, eem);
	//mien_fd->doGray(chip, gray);
	//mien_fd->doLandmark(gray, face, landmark);
	//mien_fd->doEEM(landmark, eem);
	//mien_fd->showFace(u, face);
	//mien_fd->showEEM(u, eem);
	cv::imshow("u", u);	cv::waitKey();

	return 0;
}

