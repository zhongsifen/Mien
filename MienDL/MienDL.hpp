//
//  Mien.hpp
//  Mien
//
//  Created by SIFEN ZHONG on 4/10/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef Mien_hpp
#define Mien_hpp

#include "Mien/Mien.hpp"

#include "dlib_cv.hpp"
#include "dlib_anet.hpp"
#include <dlib/image_processing/frontal_face_detector.h>

namespace MienModel {
	const std::string _MODELDAT(MienConfig::_M + "model/");
	const std::string _DAT_SP( _MODELDAT + "shape_predictor_68_face_landmarks.dat");
	const std::string _DAT_NET(_MODELDAT + "dlib_face_recognition_resnet_model_v1.dat");
}

class MienDL : public Mien {
public:
	typedef dlib::matrix<dlib::rgb_pixel> Chip_D;
	typedef dlib::matrix<float, 0, 1> Desc_D;

protected:
	dlib::frontal_face_detector _fd;
	dlib::shape_predictor _sp;
	dlib_anet::anet_type _net;

public:
	MienDL();
	~MienDL();

	bool face(Mien::Gray& gray, Mien::Face& face);
	bool landmark(Mien::Gray & gray, cv::Rect & r, Mien::Landmark & landmark);
	bool chip(Mien::Image & image, Mien::EEM & eem, Mien::EEM & tri, cv::Size & box, Mien::Chip & chip);
	bool chip(Mien::Image & image, cv::Rect & r, Mien::Chip & chip);
	bool desc(Mien::Chip & chip, Mien::Desc & desc);
	bool desc(Mien::Image & image, cv::Rect & r, Mien::Chip & chip, Mien::Desc & desc);
	//bool desc(Mien::Image & image, Mien::Chip & chip, Mien::Desc & desc);
};

#endif /* Mien_hpp */
