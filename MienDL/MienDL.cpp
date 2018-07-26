//
//  MienDL.cpp
//  Mien
//
//  Created by SIFEN ZHONG on 12/10/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "MienDL.hpp"
#include "dlib_cv.hpp"
#include <opencv2/opencv.hpp>

#include <dlib/gui_widgets.h>

MienDL::MienDL()
{
	_fd = dlib::get_frontal_face_detector();
	dlib::deserialize(MienModel::_DAT_SP) >> _sp;
	dlib::deserialize(MienModel::_DAT_NET) >> _net;
}

MienDL::~MienDL()
{

}

bool MienDL::face(Mien::Gray & gray, Mien::Face & face)
{
	std::vector<std::pair<double, dlib::rectangle>> dets;
	_fd(dlib::cv_image<uint8_t>(gray), dets);

	int n = (int)dets.size();	if (n < 1) return false;
	int i = 0;
	double p = dets[i].first;
	for (int k = 1; k < n; k++) {
		double q = dets[k].first;
		if (p < q) {
			p = q;
			i = k;
		}
	}

	dlib_cv::fdlib(dets[i].second, face);

	return true;
}

bool MienDL::landmark(Mien::Gray & gray, cv::Rect & r, Mien::Landmark & landmark)
{
	dlib::cv_image<uint8_t> gray_d(gray);
	dlib::rectangle r_d;
	dlib_cv::tdlib(r, r_d);
	dlib::full_object_detection shape = _sp(gray_d, r_d);
	int n = shape.num_parts();
	if (n < 1) return false;
	landmark.resize(n);
	for (int i = 0; i < n; i++) {
		dlib_cv::fdlib(shape.part(i), landmark[i]);
	}

	return true;
}

bool MienDL::chip(Mien::Image & image, Mien::EEM & eem, Mien::EEM & tri, cv::Size & box, Mien::Chip & chip)
{
	return Mien::chip(image, eem, tri, box, chip);
}

bool MienDL::chip(Mien::Image & image, cv::Rect & r, Mien::Chip & chip)
{
	dlib::cv_image<rgb_pixel> image_d(image);
	//dlib_cv::tdlib(image, image_d);
	//Mien::Gray gray;
	//cv::cvtColor(image, gray, CV_BGR2GRAY);
	//dlib::cv_image<uint8_t> gray_d(gray);
	dlib::rectangle r_d;
	dlib_cv::tdlib(r, r_d);
	dlib::full_object_detection shape = _sp(image_d, r_d);
	int n = shape.num_parts();
	if (n < 1) return false;
	Chip_D chip_d;
	extract_image_chip(image_d, get_face_chip_details(shape, 150, 0.25), chip_d);
	chip = dlib::toMat(chip_d);

	dlib::image_window win(chip_d);

	return true;
}

bool MienDL::desc(Mien::Chip & chip, Mien::Desc & desc)
{
	dlib::cv_image<dlib::rgb_pixel> cvimg(chip);
	dlib::matrix<rgb_pixel> chip_d;
	dlib::assign_image(chip_d, cvimg);
	std::vector<dlib::matrix<rgb_pixel>> chips(1, chip_d);
	desc = dlib::toMat(_net(chips)[0]);

	return true;
}

bool MienDL::desc(Mien::Image & image, cv::Rect & r, Mien::Chip & chip, Mien::Desc & desc)
{
	dlib::cv_image<rgb_pixel> image_d;
	dlib_cv::tdlib(image, image_d);
	Mien::Gray gray;
	cv::cvtColor(image, gray, CV_BGR2GRAY);
	dlib::cv_image<uint8_t> gray_d(gray);
	dlib::rectangle r_d;
	dlib_cv::tdlib(r, r_d);
	dlib::full_object_detection shape = _sp(gray_d, r_d);
	int n = shape.num_parts();
	if (n < 1) return false;
	Chip_D chip_d;
	extract_image_chip(image_d, get_face_chip_details(shape, 150, 0.25), chip_d);
	chip = dlib::toMat(chip_d);
	std::vector<dlib::matrix<rgb_pixel>> chips(1, chip_d);
	desc = dlib::toMat(_net(chips)[0]);

	return true;
}
