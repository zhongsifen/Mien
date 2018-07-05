//
//  Mien58.hpp
//  Mien58
//
//  Created by SIFEN ZHONG on 26/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef Mien58_hpp
#define Mien58_hpp
	
#include "Mien/Mien.hpp"
#include "MienDL/MienDL.hpp"

class Mien58 {
	MienDL _mien;
	std::vector<dlib::matrix<dlib::rgb_pixel>> _chips;
	std::vector<dlib::matrix<float, 0, 1>> _descrs;
public:
	bool setup();
	bool setupCard(cv::Mat& img);
	bool setupCard(std::vector<cv::Mat>& imgs);
	bool run(cv::Mat& img, int& id, cv::Mat& ch);
};

#endif /* Mien58_hpp */
