//
//  MienDL.cpp
//  Mien
//
//  Created by SIFEN ZHONG on 12/10/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "MienDL.hpp"
#include "dlib_cv.hpp"

MienDL::MienDL() {
	_fd = dlib::get_frontal_face_detector();
	dlib::deserialize(MienConst::_DAT_SP) >> _sp;
	dlib::deserialize(MienConst::_DAT_NET) >> _net;
}

bool MienDL::detect(cv::Mat& gray, cv::Rect& face, std::vector<cv::Point>& landmarklist) {
	//std::vector<Landmark> landmarks;
	dlib::cv_image<uint8_t> dlimg(gray);
	std::vector<std::pair<double, dlib::rectangle>> dets;
	_fd(dlimg, dets);

	int n = (int)dets.size();	if (n < 1) return false;
	int i = 0;
	//dlib_cv::fdlib(dets[i].second, face);
	dlib::full_object_detection fo = _sp(dlimg, dets[i].second);
	dlib_cv::fdlib(fo.get_rect(), face);
	landmarklist.resize(_nfp);
	for (int k = 0; k < _nfp; k++) {
		dlib_cv::fdlib(fo.part(k), landmarklist[k]);
	}

	return true;
}

bool MienDL::descr(cv::Mat& cvimg, dlib::matrix<rgb_pixel>& chip, dlib::matrix<float,0,1>& descr) {
	dlib::cv_image<rgb_pixel> img;
	dlib_cv::tdlib(cvimg, img);
	std::vector<matrix<rgb_pixel>> faces;
	for (auto face : _fd(img)) {
		auto shape = _sp(img, face);
		if (shape.num_parts() > 0) {
			matrix<rgb_pixel> face_chip;
			extract_image_chip(img, get_face_chip_details(shape,150,0.25), face_chip);
			faces.push_back(std::move(face_chip));
		}
	}
	if (faces.size() < 1) return false;
	std::vector<matrix<float,0,1>> face_descriptors = _net(faces);
	chip = faces[0];
	descr = face_descriptors[0];

	return true;
}
