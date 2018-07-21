#pragma once

#include <opencv2/core.hpp>

class Mien {
public:
	typedef cv::Mat Image;
	typedef cv::Mat_<uint8_t> Gray;
	typedef cv::Rect Face;
	typedef std::vector<cv::Point> Landmark;
	typedef cv::Mat Chip;
	typedef cv::Mat Desc;
	typedef std::vector<cv::Point2f> EEM;

protected:
	const int _nfp = 68;	// number of feature points

public:
	Mien() {  }
	~Mien() {  }

	bool gray(Image & image, Gray & gray);
	bool eem(Landmark landmark, EEM & eem);
	bool chip(Image & image, EEM & eem, EEM & tri, cv::Size & box, Chip & chip);
	float measure(Desc & d1, Desc & d2);

	void showFace(cv::Mat & img, Face & face);
	void showLandmark(cv::Mat & img, Landmark & landmark);
	void showEEM(cv::Mat & img, EEM & eem);
};