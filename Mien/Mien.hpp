#pragma once

#include <opencv2/core.hpp>

namespace MienType {
	typedef cv::Mat Image;
	typedef cv::Mat_<uint8_t> Gray;
	typedef cv::Rect Face;
	typedef std::vector<cv::Point> Landmark;
	typedef cv::Mat Chip;
	typedef cv::Mat Desc;
	typedef std::vector<cv::Point2f> EEM;
}

class Mien {
protected:
	const int _nfp = 68;	// number of feature points

public:
	Mien() {  }
	~Mien() {  }

	bool gray(MienType::Image & image, MienType::Gray & gray);
	bool eem(MienType::Landmark landmark, MienType::EEM & eem);
	bool chip(MienType::Image & image, MienType::EEM & eem, MienType::EEM & tri, cv::Size & box, MienType::Chip & chip);
	float measure(MienType::Desc & d1, MienType::Desc & d2);

	void showFace(cv::Mat & img, MienType::Face & face);
	void showLandmark(cv::Mat & img, MienType::Landmark & landmark);
	void showEEM(cv::Mat & img, MienType::EEM & eem);
};