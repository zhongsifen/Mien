// Mien.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "Mien.hpp"
#include "MienLandmark.hpp"
#pragma comment(lib, "libfacedetect-x64.lib")
#
#if 0
bool Mien::landmark68(cv::Mat& gray, cv::Rect& face, std::vector<cv::Point>& landmark) {
	for (int i = 0; i < n; i++)
	{
		short * p = ((short*)(_result + 1)) + 142 * i;
		int x = p[0];
		int y = p[1];
		int w = p[2];
		int h = p[3];
		int neighbors = p[4];
		int angle = p[5];

		printf("face_rect=[%d, %d, %d, %d], neighbors=%d, angle=%d\n", x, y, w, h, neighbors, angle);
		rectangle(result_frontal, Rect(x, y, w, h), Scalar(0, 255, 0), 2);
		if (doLandmark)
		{
			for (int j = 0; j < 68; j++)
				circle(result_frontal, Point((int)p[6 + 2 * j], (int)p[6 + 2 * j + 1]), 1, Scalar(0, 255, 0));
		}
	}

	return true;
}
#endif

bool Mien::landmark_1(cv::Mat & gray, cv::Rect & face, std::vector<cv::Point>& landmark)
{
	int* na = facedetect_frontal(_p, gray.data, gray.cols, gray.rows, (int)gray.step);
	if (na == nullptr) return false;
	int n = na[0];	assert(n == 1);
	short* sa = (short*)&na[1];
	int si = 0;
	int x = sa[si++];
	int y = sa[si++];
	int w = sa[si++];
	int h = sa[si++];
	face = cv::Rect(x, y, w, h);
	int neighbors = sa[si++];
	int angle = sa[si++];

	landmark.reserve(_nfp);
	for (int i = 0; i < _nfp; i++) {
		int x = sa[si++];
		int y = sa[si++];
		landmark[i] = cv::Point(x, y);
	}
	return true;
}
