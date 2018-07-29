//
//  MienDL.hpp
//  Mien
//
//  Created by SIFEN ZHONG on 4/10/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef Mien_hpp
#define Mien_hpp

#include "Mien/Mien.hpp"

#include <opencv2/opencv.hpp>
#include "dlib_anet.hpp"
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/opencv.h>

namespace MienModel {
	const std::string _MODELDAT(MienConfig::_M + "model/");
	const std::string _DAT_SP( _MODELDAT + "shape_predictor_68_face_landmarks.dat");
	const std::string _DAT_NET(_MODELDAT + "dlib_face_recognition_resnet_model_v1.dat");
}

class MienDL : public Mien {
public:
	typedef dlib::matrix<dlib::rgb_pixel> Image_D;
	typedef dlib::matrix<unsigned char> Gray_D;
	typedef dlib::matrix<dlib::rgb_pixel> Chip_D;
	typedef dlib::matrix<float, 0, 1> Desc_D;
	typedef dlib::cv_image<dlib::bgr_pixel> ImageCV_D;

protected:
	dlib::frontal_face_detector _fd;
	dlib::shape_predictor _sp;
	dlib_anet::anet_type _net;

public:
	MienDL();
	~MienDL();

	bool doFace(Gray& gray, Face& face);
	bool doLandmark(Gray & gray, cv::Rect & r, Landmark & landmark);
	bool doChip(Image & image, cv::Rect & r, Chip & chip);
	bool doDesc(Chip & chip, Desc & desc);
	bool doDesc(Image & image, cv::Rect & r, Chip & chip, Desc & desc);
	
	static void fdlib(Image_D & image_d, Image & image);
	static void fdlib(Gray_D & gray_d, Gray & gray);
	static void tdlib(Image & image, Image_D & image_d);
	static void tdlib(Gray & gray, Gray_D & gray_d);

};

#endif /* Mien_hpp */
