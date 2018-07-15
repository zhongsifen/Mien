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

MienDL::MienDL() {
	_fd = dlib::get_frontal_face_detector();
	dlib::deserialize(MienConst::_DAT_SP) >> _sp;
	dlib::deserialize(MienConst::_DAT_NET) >> _net;
}

bool MienDL::detect(cv::Mat& gray, cv::Rect& face, std::vector<cv::Point>& landmark) {
	dlib::cv_image<uint8_t> dlimg(gray);
	std::vector<std::pair<double, dlib::rectangle>> dets;
	_fd(dlimg, dets);

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

	dlib::full_object_detection fo = _sp(dlimg, dets[i].second);
	dlib_cv::fdlib(fo.get_rect(), face);
	int nfp = fo.num_parts();
	landmark.resize(nfp);
	for (int k = 0; k < nfp; k++) {
		dlib_cv::fdlib(fo.part(k), landmark[k]);
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

bool MienDL::descr(cv::Mat& img, dlib::matrix<float, 0, 1>& dsc) {
	dlib::cv_image<dlib::rgb_pixel> cvimg(img);
	dlib::matrix<rgb_pixel> chip;
	dlib::assign_image(chip, cvimg);
	std::vector<dlib::matrix<rgb_pixel>> chips;
	chips.push_back(chip);
	chips[0] = chip;
	std::vector<dlib::matrix<float, 0, 1>> dscs = _net(chips);
	dsc = dscs[0];

	//dsc = _net(chip);

	return true;
}

///////////////////////////////////////////////////////////////////////

//bool MienDL::face(MienType::Gray & gray, MienType::Face & face)
//{
//	dlib_cv::fdlib(_fd(dlib::cv_image<uint8_t>(gray))[0], face);
//
//	return true;
//}

bool MienDL::face(MienType::Gray & gray, MienType::Face & face)
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

bool MienDL::landmark(MienType::Gray & gray, cv::Rect & r, MienType::Landmark & landmark)
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

bool MienDL::chip(MienType::Image & image, cv::Rect & r, MienType::Chip & chip)
{
	dlib::cv_image<rgb_pixel> image_d;
	dlib_cv::tdlib(image, image_d);
	MienType::Gray gray;
	cv::cvtColor(image, gray, CV_BGR2GRAY);
	dlib::cv_image<uint8_t> gray_d(gray);
	dlib::rectangle r_d;
	dlib_cv::tdlib(r, r_d);
	dlib::full_object_detection shape = _sp(gray_d, r_d);
	int n = shape.num_parts();
	if (n < 1) return false;
	MienType::Chip_D chip_d;
	extract_image_chip(image_d, get_face_chip_details(shape, 150, 0.25), chip_d);
	chip = dlib::toMat(chip_d);

	return true;
}

bool MienDL::desc(MienType::Chip & chip, MienType::Desc_D & desc)
{
	dlib::cv_image<dlib::rgb_pixel> cvimg(chip);
	dlib::matrix<rgb_pixel> chip_d;
	dlib::assign_image(chip_d, cvimg);
	std::vector<dlib::matrix<rgb_pixel>> chips(1, chip_d);
	std::vector<dlib::matrix<float, 0, 1>> dscs = _net(chips);
	desc = dscs[0];
	desc = _net(chips)[0];

	return true;
}

bool MienDL::desc(MienType::Image& image, MienType::Chip& chip, MienType::Desc_D& desc) {
	dlib::cv_image<rgb_pixel> img;
	dlib_cv::tdlib(image, img);
	std::vector<matrix<rgb_pixel>> faces;
	for (auto face : _fd(img)) {
		auto shape = _sp(img, face);
		if (shape.num_parts() > 0) {
			matrix<rgb_pixel> face_chip;
			extract_image_chip(img, get_face_chip_details(shape, 150, 0.25), face_chip);
			faces.push_back(std::move(face_chip));
		}
	}
	if (faces.size() < 1) return false;
	std::vector<matrix<float, 0, 1>> face_descriptors = _net(faces);
	chip = dlib::toMat(faces[0]);
	desc = face_descriptors[0];

	return true;
}

//bool MienDL::desc_(MienType::Image& image, MienType::Chip& chip, MienType::Desc_D& desc) {
//	dlib::cv_image<rgb_pixel> img;
//	dlib_cv::tdlib(image, img);
//	std::vector<matrix<rgb_pixel>> faces;
//	for (auto face : _fd(img)) {
//		auto shape = _sp(img, face);
//		if (shape.num_parts() > 0) {
//			matrix<rgb_pixel> face_chip;
//			extract_image_chip(img, get_face_chip_details(shape, 150, 0.25), face_chip);
//			faces.push_back(std::move(face_chip));
//		}
//	}
//	if (faces.size() < 1) return false;
//	std::vector<matrix<float, 0, 1>> face_descriptors = _net(faces);
//	chip = dlib::toMat(faces[0]);
//	desc = face_descriptors[0];
//
//	return true;
//}
