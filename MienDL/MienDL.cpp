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

bool MienDL::doFace(Gray & gray, Face & face)
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

bool MienDL::doLandmark(Gray & gray, cv::Rect & r, Landmark & landmark)
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

bool MienDL::doChip(Image & image, cv::Rect & r, Chip & chip)
{
	Image_D image_d;
	tdlib(image, image_d);
	dlib::rectangle r_d;
	dlib_cv::tdlib(r, r_d);
	dlib::full_object_detection shape = _sp(image_d, r_d);
	int n = shape.num_parts();	if (n < 1) return false;
	Chip_D chip_d;
	extract_image_chip(image_d, get_face_chip_details(shape, 150, 0.25), chip_d);
	fdlib(chip_d, chip);

	return true;
}

bool MienDL::doDesc(Chip & chip, Desc & desc)
{
	Chip_D chip_d;
	tdlib(chip, chip_d);
	std::vector<Chip_D> chips(1, chip_d);
	desc = dlib::toMat(_net(chips)[0]);

	return true;
}

bool MienDL::doDesc(Image & image, cv::Rect & r, Chip & chip, Desc & desc)
{
	Image_D image_d;
	tdlib(image, image_d);
	Gray gray;
	doGray(image, gray);
	Gray_D gray_d;
	tdlib(gray, gray_d);
	dlib::rectangle r_d;
	dlib_cv::tdlib(r, r_d);
	dlib::full_object_detection shape = _sp(gray_d, r_d);
	int n = shape.num_parts();
	if (n < 1) return false;
	Chip_D chip_d;
	extract_image_chip(image_d, get_face_chip_details(shape, 150, 0.25), chip_d);
	chip = dlib::toMat(chip_d);
	std::vector<Chip_D> chips(1, chip_d);
	desc = dlib::toMat(_net(chips)[0]);

	return true;
}

void MienDL::fdlib(Image_D & image_d, Image & image)
{
	cv::Mat image_r(num_rows(image_d), num_columns(image_d), CV_8UC3, image_data(image_d), width_step(image_d));
	cv::cvtColor(image_r, image, CV_RGB2BGR);
}

void MienDL::fdlib(Gray_D & gray_d, Gray & gray)
{
	cv::Mat gray_r(num_rows(gray_d), num_columns(gray_d), CV_8UC3, image_data(gray_d), width_step(gray_d));
	gray = gray_r.clone();
}

void MienDL::tdlib(Image & image, Image_D & image_d)
{
	ImageCV_D imagecv_d(image);
	dlib::assign_image(image_d, imagecv_d);
}

void MienDL::tdlib(Gray & gray, Gray_D & gray_d)
{
	ImageCV_D graycv_d(gray);
	dlib::assign_image(gray_d, graycv_d);
}
