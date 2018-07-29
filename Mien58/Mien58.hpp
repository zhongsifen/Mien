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
#include "MienFD/MienFD.hpp"

class Mien58 {
	// dlib_face_recognition_resnet_model_v1.dat uses (150, 150)
	const cv::Size _r = cv::Size(150, 150);
	const cv::Point2f _e1 = cv::Point2f(47, 44);
	const cv::Point2f _e2 = cv::Point2f(103, 44);
	const cv::Point2f _m = cv::Point2f(75, 102);

	MienDL _mien_dl;
	MienFD _mien_fd;
	Mien::EEM _tri;
	cv::Size _box;
public:
	void getTri(Mien::EEM & tri, cv::Size & box) { tri = _tri; box = _box; }
	MienDL* getMienDL() { return &_mien_dl; }
	MienFD* getMeinFD() { return &_mien_fd; }
	bool setup();
	bool setupCard(cv::Mat& img);
};

#endif /* Mien58_hpp */
