#pragma once

#include <opencv2/core.hpp>

class Mien {
	const int _nfp = 68;	// number of feature points
	unsigned char* _p;

public:
	Mien(int a = 0x20000) { _p = new unsigned char[a]; }

	bool landmark_1(cv::Mat& gray, cv::Rect& face, std::vector<cv::Point>& landmark);
	bool landmark_n(cv::Mat& gray, int& n, std::vector<cv::Rect>& face_n, std::vector<std::vector<cv::Point>>& landmark_n);
};