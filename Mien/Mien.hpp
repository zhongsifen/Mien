#pragma once

#include "MienConfig.hpp"
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
	const static int _nfp =  68;	// number of feature points
	const static int _ndv = 128;	// number of description values

public:
	static bool doGray(Image & image, Gray & gray);
	static bool doEEM(Landmark & landmark, EEM & eem);
	static bool doChipTri(Image & image, EEM & eem, EEM & tri, cv::Size & box, Chip & chip);
	static float doMeasure(Desc & d1, Desc & d2);

	static void showFace(cv::Mat & img, Face & face);
	static void showLandmark(cv::Mat & img, Landmark & landmark);
	static void showEEM(cv::Mat & img, EEM & eem);
};