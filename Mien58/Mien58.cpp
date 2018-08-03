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
	_tri[1] = _e2;
	_tri[2] = _m;
	_box = _r;

	return true;
}

bool Mien58::setup(int rows, int cols)
{
	setup();
	_mien_nn.setup(rows, cols);

	return true;
}

bool Mien58::setupCard(cv::Mat &img) {
	
	return true;
}
