#include "MienNN.hpp"


bool Mnn::doLandmark(Mien::Image & image, Mien::Face & face, Mien::Landmark & landmark)
{
	std::vector<Bbox> bboxs;
	detect(image, bboxs);
	int n = bboxs.size();
	if (n < 1) return false;
	int k = 0;
	float score = bboxs[k].score;
	for (int i = 1; i < n; i++) {
		if (score < bboxs[i].score) {
			score = bboxs[k = i].score;
		}
	}
	MienNN::fnn(bboxs[k], face, landmark);

	return true;
}

bool MienNN::setup(int rows, int cols)
{
	nn = new Mnn(rows, cols);

	return true;
}

bool MienNN::doLandmark(Mien::Image & image, Mien::Face & face, Mien::Landmark & landmark)
{
	return nn->doLandmark(image, face, landmark);
}

void MienNN::fnn(Bbox & bbox, Mien::Face & face, Mien::Landmark & landmark)
{
	face = cv::Rect(cv::Point(bbox.y1, bbox.x1), cv::Point(bbox.y2, bbox.x2));
	float* pp = bbox.ppoint;
	int n = 5;
	landmark.resize(n);
	for (int i = 0; i < n; i++) {
		landmark[i] = cv::Point2f(pp[i], pp[i+5]);
	}
}

bool _EEM(std::vector<Bbox> & bboxs, Mien::Face & face, Mien::EEM & eem)
{
	int n = bboxs.size();	if (n < 1) return false;
	int k = 0;
	float area = bboxs[k].area;
	for (int i = 1; i < n; n++) {
		if (area < bboxs[i].area) {
			k = i;
			area = bboxs[k].area;
		}
	}
	Bbox* box = &bboxs[k];
	float* pp = box->ppoint;
	face = cv::Rect(cv::Point(box->y1, box->x1), cv::Point(box->y2, box->x2));
	eem.resize(3);
	eem[0] = cv::Point2f(pp[0], pp[5]);
	eem[1] = cv::Point2f(pp[1], pp[6]);
	eem[2] = (cv::Point2f(pp[3], pp[8]) + cv::Point2f(pp[4], pp[9])) / 2;

	return true;
}
