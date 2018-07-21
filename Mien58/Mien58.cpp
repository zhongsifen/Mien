//
//  Mien58.cpp
//  Mien58
//
//  Created by SIFEN ZHONG on 26/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "Mien58.hpp"

bool Mien58::setup()
{
	_tri.resize(3);
	_tri[0] = _e1;
	_tri[1] = Mien58::_e2;
	_tri[2] = Mien58::_m;
	_box = Mien58::_r;

	return true;
}

bool Mien58::setupCard(cv::Mat &img) {
	cv::Rect face;
	std::vector<cv::Point> landmark;
	std::vector<cv::Point2f> eem;
	
	return true;
}

bool Mien58::runFace(Mien::Image & image, Mien::Face & face)
{
	Mien::Gray gray;
	this->_mien.gray(image, gray);
	this->_mien.face(gray, face);

	return true;
}
#if 0
	cv::Mat w = image.clone();
	this->_mien.showFace(w, face);
	cv::imshow("w", w);	cv::waitKey();

	//Mien::Chip chip;
	//Mien::Desc desc;
	//bool ret = _mien.desc(img, chip, desc);	if (!ret) return false;
	//double score = 100;
	//int index = id = -1;
	//int n = (int)_descrs.size();
	//for (int i=0; i<n; ++i) {
	//	double s = dlib::length(descr - _descrs[i]);
	//	if (s < score) {
	//		score = s;
	//		index = i;
	//	}
	//}
	//if (score > 0.6) return false;
	//id = index;
	//dlib::array2d<dlib::rgb_pixel> chip_img;
	//dlib::assign_image(chip_img, _chips[id]);
	//dlib_cv::fdlib(chip_img, ch);

	//
	return true;
}
#endif