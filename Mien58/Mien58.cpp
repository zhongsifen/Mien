//
//  Mien58.cpp
//  Mien58
//
//  Created by SIFEN ZHONG on 26/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "Mien58.hpp"

bool Mien58::setup() {
	
	return true;
}

bool Mien58::setupCard(cv::Mat &img) {
	cv::Rect face;
	std::vector<cv::Point> landmark;
	std::vector<cv::Point2f> eem;
	
	return true;
}

bool Mien58::setupCard(std::vector<cv::Mat> &imgs) {
	int n = (int)imgs.size();
	_chips.resize(n);
	_descrs.resize(n);
	for (int i=0; i<n; ++i) {
		//_mien.descr(imgs[i], _chips[i], _descrs[i]);
	}
	
	return true;
}

bool Mien58::run(cv::Mat &img, int &id, cv::Mat &ch) {
	//MienType::Chip chip;
	//MienType::Desc desc;
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