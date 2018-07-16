#pragma once

#include <opencv2/core.hpp>
#include <dlib/array2d.h>

namespace MienType {
	typedef cv::Mat Image;
	typedef cv::Mat_<uint8_t> Gray;
	typedef cv::Rect Face;
	typedef std::vector<cv::Point> Landmark;
	typedef cv::Mat Chip;
	typedef cv::Mat Desc;

	typedef dlib::matrix<dlib::rgb_pixel> Chip_D;
	typedef dlib::matrix<float, 0, 1> Desc_D;
}

class Mien {
protected:
	const int _nfp = 68;	// number of feature points

public:
	Mien() {  }
	~Mien() {  }

	bool virtual detect(cv::Mat& g, cv::Rect& face, std::vector<cv::Point>& landmark) = 0;
	bool eem(std::vector<cv::Point>& landmark, std::vector<cv::Point2f>& eem);
	bool align(cv::Mat& g, std::vector<cv::Point2f>& eem, std::vector<cv::Point2f>& tri, cv::Size box, cv::Mat& h);

	void showFace(cv::Mat & img, MienType::Face & face);
	void showLandmark(cv::Mat& img, MienType::Landmark & landmark);
	void showEEM(cv::Mat & img, std::vector<cv::Point2f> eem);
};