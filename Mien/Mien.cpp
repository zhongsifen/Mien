// Mien.cpp : Defines the exported functions for the DLL application.
//

#include "Mien.hpp"
#include "opencv2/imgproc.hpp"

void Mien::showFace(cv::Mat & img, cv::Rect & face) {
	cv::rectangle(img, face, cv::Scalar(0x00, 0xFF, 0x00));
}

void Mien::showLandmark(cv::Mat & img, std::vector<cv::Point>& landmark) {
	for (int k = 0; k < landmark.size(); k++) {
		cv::circle(img, landmark[k], 2, cv::Scalar(0xFF, 0x00, 0x00));
	}
};
