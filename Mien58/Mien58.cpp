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
	_mien.gray(image, gray);
	return _mien.face(gray, face);
}

bool Mien58::runChip(Mien::Image & image, cv::Rect & r, Mien::Chip & chip)
{
	return _mien.chip(image, r, chip);
}

bool Mien58::runDesc(Mien::Chip & chip, Mien::Desc & desc)
{
	return _mien.desc(chip, desc);
}
