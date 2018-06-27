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
#include "MienNet.hpp"

namespace MienConst {
	const std::string _MODELDAT(MienConfig::_M + "model/");
	const std::string _DAT_SP( _MODELDAT + "shape_predictor_68_face_landmarks.dat");
	const std::string _DAT_NET(_MODELDAT + "dlib_face_recognition_resnet_model_v1.dat");

	const cv::Point2f _eyeL(46, 21);
	const cv::Point2f _eyeR(18, 21);
	const cv::Size _box(64, 64);
	const std::vector<cv::Point2f> _lrn = { _eyeL, _eyeR, };
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

	bool detect(cv::Mat& gray, cv::Rect& face, std::vector<cv::Point>& landmark);

	bool detect(cv::Mat& img, std::vector<Landmark>& landmarks);
	bool beone(std::vector<Landmark>& landmarks, Landmark& landmark);
	bool align(cv::Mat& f, Landmark& landmark, cv::Mat& h);
	
	//void showLandmark(cv::Mat& img, Landmark& landmark);
	
	bool descr(cv::Mat& img, dlib::matrix<dlib::rgb_pixel>& chip, dlib::matrix<float,0,1>& descr);
};

#endif /* Mien_hpp */
