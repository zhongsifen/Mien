#include "MienNN.hpp"

bool Mnn::doLandmark(Mien::Image & image, Mien::Face & face, Mien::EEM & eem)
{
	findFace(image);
	int n = thirdBbox_.size();	if (n < 1) return false;
	int k = 0;
	float area = thirdBbox_[k].area;
	for (int i = 1; i < n; n++) {
		if (area < thirdBbox_[i].area) {
			k = i;
			area = thirdBbox_[k].area;
		}
	}
	Bbox* box = &thirdBbox_[k];
	float* pp = box->ppoint;
	face = cv::Rect(cv::Point(box->x1, box->y1), cv::Point(box->x2, box->y2));
	eem.resize(3);
	eem[0] = cv::Point2f(pp[0], pp[5]);
	eem[1] = cv::Point2f(pp[1], pp[6]);
	eem[2] = (cv::Point2f(pp[3], pp[8]) + cv::Point2f(pp[4], pp[9]))/2;

	return true;
}

MienNN::setup(int rows, int cols)
{
	nn = new Mnn(rows, cols);

}