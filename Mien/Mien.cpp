// Mien.cpp : Defines the exported functions for the DLL application.
//

#include "Mien.hpp"
#include "opencv2/imgproc.hpp"

bool Mien::eem(MienType::Landmark landmark, MienType::EEM & eem)
{
	cv::Point2f e1f(landmark[36]);
	cv::Point2f e1n(landmark[39]);
	cv::Point2f e2f(landmark[45]);
	cv::Point2f e2n(landmark[42]);
	cv::Point2f m1(landmark[48]);
	cv::Point2f m2(landmark[54]);

	eem.resize(3);
	eem[0] = (e1f + e1n) / 2;
	eem[1] = (e2f + e2n) / 2;
	eem[2] = (m1 + m2) / 2;

	return true;
}

bool Mien::chip(MienType::Image & image, MienType::EEM & eem, MienType::EEM & tri, cv::Size & box, MienType::Chip & chip)
{
	cv::Mat aff = cv::getAffineTransform(eem, tri);
	cv::warpAffine(image, chip, aff, box);
	
	return true;
}

void Mien::showFace(cv::Mat & img, MienType::Face & face)
{
	cv::rectangle(img, face, cv::Scalar(0x00, 0xFF, 0x00));
}

void Mien::showLandmark(cv::Mat & img, MienType::Landmark & landmark)
{
	for (int k = 0; k < landmark.size(); k++) {
		cv::circle(img, landmark[k], 2, cv::Scalar(0xFF, 0x00, 0x00));
	}
}

void Mien::showEEM(cv::Mat & img, MienType::EEM & eem) {
	for (int k = 0; k < eem.size(); k++) {
		cv::circle(img, eem[k], 2, cv::Scalar(0xFF, 0xFF, 0x00));
	}
}
