#include "MienST.hpp"

MienST::MienST()
{
	stage = NONE;
	init();
}

bool MienST::init()
{
	if (stage < INIT) {
		fd = new seeta::FaceDetection(MienConfig::_S + "seeta_fd_frontal_v1.0.bin");	if (fd == nullptr) return false;
		fa = new seeta::FaceAlignment(MienConfig::_S + "seeta_fa_v1.1.bin");			if (fa == nullptr) return false;
		fr = new seeta::FaceIdentification(MienConfig::_S + "seeta_fr_v1.0.bin");		if (fr == nullptr) return false;
	}

	stage = INIT;

	return true;
}

bool MienST::doFace(Gray & gray, Face & face)
{
	if (stage < INIT) return false;

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
	if (score < 0.5F) return false;
	face_st = faces[k];
	seeta::Rect* box = &face_st.bbox;
	face = cv::Rect(box->x, box->y, box->width, box->height);

	stage = FACE;

	return true;
}

bool MienST::doLandmark(Gray & gray, Landmark & landmark)
{
	if (face_st.score < 0.01) return false;
	seeta::ImageData gray_st;
	tst(gray, gray_st);
	fa->PointDetectLandmarks(gray_st, face_st, landmark_st);
	fst(landmark_st, landmark);

	return true;
}

void MienST::tst(Image & image, seeta::ImageData & image_st)
{
	image_st.width  = image.cols;
	image_st.height = image.rows;
	image_st.num_channels = image.channels();
	image_st.data = image.data;
}
void MienST::fst(seeta::FaceLandmark & landmark_st, Landmark & landmark)
{
	int n = 5;
	landmark.resize(n);
	for (int i = 0; i < n; i++) {
		landmark[i] = cv::Point2f((float)landmark_st[i].x, (float)landmark_st[i].y);
	}
}
