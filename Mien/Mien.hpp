#pragma once

#include <opencv2/core.hpp>

class Mien {
protected:
	const int _nfp = 68;	// number of feature points

public:
	Mien() {  }
	~Mien() {  }

	bool virtual detect(cv::Mat& g, cv::Rect& face, std::vector<cv::Point>& landmark) = 0;
	bool eem(std::vector<cv::Point>& landmark, std::vector<cv::Point2f>& eem);
	bool align(cv::Mat& g, std::vector<cv::Point2f>& eem, std::vector<cv::Point2f>& tri, cv::Size box, cv::Mat& h);

	void showFace(cv::Mat & img, cv::Rect & face);
	void showLandmark(cv::Mat& img, std::vector<cv::Point>& landmark);
	void showEEM(cv::Mat & img, std::vector<cv::Point2f> eem);
};