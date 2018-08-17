#include "MienST.hpp"

MienST::MienST()
{
	fd = new seeta::FaceDetection(MienConfig::_S + "seeta_fd_frontal_v1.0.bin");
	fa = new seeta::FaceAlignment(MienConfig::_S + "seeta_fa_v1.1.bin");
}

bool MienST::doFace(Gray & gray, Face & face)
{
	seeta::ImageData img_data;
	img_data.data = gray.data;
	img_data.width = gray.cols;
	img_data.height = gray.rows;
	img_data.num_channels = 1;
	std::vector<seeta::FaceInfo> faces = fd->Detect(img_data);

	int n = (int)faces.size();	if (n < 1) return false;
	int k = 0;
	double score = faces[k].score;
	for (int i = 1; i < n; i++) {
		if (score < faces[i].score) {
			score = faces[k = i].score;
		}
	}
	face_st = faces[k];
	seeta::Rect* box = &face_st.bbox;
	face = cv::Rect(box->x, box->y, box->width, box->height);

	return true;
}

bool MienST::doLandmark(Gray & gray, cv::Rect & r, Landmark & landmark)
{
	return true;
}
