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
#include "MienConfig.hpp"

#include "dlib_cv.hpp"
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/dnn.h>
#include "MienAnet.hpp"

namespace MienModel {
	const std::string _MODELDAT(MienConfig::_M + "model/");
	const std::string _DAT_SP( _MODELDAT + "shape_predictor_68_face_landmarks.dat");
	const std::string _DAT_NET(_MODELDAT + "dlib_face_recognition_resnet_model_v1.dat");
}

class Landmark {
public:
	double weight;
	cv::Rect box;
	std::vector<cv::Point2f> lrn;
};

class MienDL : public Mien {
protected:
	dlib::frontal_face_detector _fd;
	dlib::shape_predictor _sp;
	anet_type _net;

public:
	MienDL();
	~MienDL();

	bool face(MienType::Gray& gray, MienType::Face& face);
	bool landmark(MienType::Gray & gray, cv::Rect & r, MienType::Landmark & landmark);
	bool chip(MienType::Image & image, MienType::EEM & eem, MienType::EEM & tri, cv::Size & box, MienType::Chip & chip);
	bool chip(MienType::Image & image, cv::Rect & r, MienType::Chip & chip);
	bool desc(MienType::Chip & chip, MienType::Desc & desc);
	bool desc(MienType::Image & image, cv::Rect & r, MienType::Chip & chip, MienType::Desc & desc);
	//bool desc(MienType::Image & image, MienType::Chip & chip, MienType::Desc & desc);
};

#endif /* Mien_hpp */
