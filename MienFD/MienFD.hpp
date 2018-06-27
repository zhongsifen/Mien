#pragma once

#include "Mien/Mien.hpp"

class MienFD : public Mien {
	unsigned char* _p;		// storage for computation

public:
	MienFD(int a = 0x20000) { _p = new unsigned char[a]; }
	~MienFD() { delete[] _p; }

	bool detect(cv::Mat& gray, cv::Rect& face, std::vector<cv::Point>& landmark);
};