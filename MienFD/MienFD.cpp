// Mien.cpp : Defines the exported functions for the DLL application.
//

#include "MienFD.hpp"
#include "opencv2/imgproc.hpp"

int * facedetect_frontal(
	unsigned char * result_buffer,//buffer memory for storing face detection results, !!its size must be 0x20000 Bytes!!
	unsigned char * gray_image_data, int width, int height, int step,//input image, it must be gray (single-channel) image!
	float scale = 1.2f, //scale factor for scan windows
	int min_neighbors = 2, //Number of neighbors each candidate rectangle should have to retain it
	int min_object_width = 48, //Minimum possible face size. Faces smaller than that are ignored.
	int max_object_width = 0, //Maximum possible face size. Faces larger than that are ignored. It is the largest posible when max_object_width=0.
	int doLandmark = 1); // Do landmark detection or not
#pragma comment(lib, "libfacedetect-x64.lib")

bool MienFD::doLandmark(Gray & gray, Face & face, Landmark & landmark)
{
	int* na = facedetect_frontal(_p, gray.data, gray.cols, gray.rows, (int)gray.step);	if (na == nullptr) return false;
	int n = na[0];	assert(n == 1);
	short* sa = (short*)&na[1];
	int k = 0;
	int x = sa[k++];
	int y = sa[k++];
	int w = sa[k++];
	int h = sa[k++];
	face = cv::Rect(x, y, w, h);
	int neighbors = sa[k++];
	int angle = sa[k++];
	printf("neighbors, angle = %d, %d\n", neighbors, angle);

	landmark.resize(_nfp);
	for (int i = 0; i < _nfp; i++) {
		int x = sa[k++];
		int y = sa[k++];
		landmark[i] = cv::Point(x, y);
	}

	return true;
}
