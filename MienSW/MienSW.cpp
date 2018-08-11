#include "MienSW.hpp"
#include "MienConfig.hpp"

MienSW::MienSW()
{
	FD = new seeta::FaceDetector2((MienConfig::_S + "SeetaFaceDetector2.0.ats").c_str());
	PD = new seeta::PointDetector2((MienConfig::_S + "SeetaPointDetector2.0.pts5.ats").c_str());
	FR = new seeta::FaceRecognizer2((MienConfig::_S + "SeetaFaceRecognizer2.0.ats").c_str());
}

bool MienSW::doFace(Image & image, Face & face)
{
	seeta::cv::ImageData image_sw = image;
	SeetaRect *face_sw = FD->Detect(image_sw);	if (face_sw == nullptr) return false;
	fsw(*face_sw, face);

	return true;
}

bool MienSW::doLandmark(Image & image, Face & face, Landmark & landmark)
{
	seeta::cv::ImageData image_sw = image;
	SeetaRect face_sw;
	tsw(face, face_sw);
	SeetaPointF landmark_sw[5];
	PD->DetectEx(image_sw, face_sw, landmark_sw);
	fsw(landmark_sw, landmark);

	return true;
}

void MienSW::fsw(SeetaRect & face_sw, Face & face)
{
	face = Face(face_sw.x, face_sw.y, face_sw.width, face_sw.height);
}

void MienSW::fsw(SeetaPointF landmark_sw[], Landmark & landmark)
{
	int n = 5;
	landmark.resize(n);
	for (int i = 0; i < n; i++) {
		landmark[i] = cv::Point((int)landmark_sw[i].x, (int)landmark_sw[i].y);
	}
}

void MienSW::tsw(Face & face, SeetaRect & face_sw)
{
	face_sw.x = face.x;
	face_sw.y = face.y;
	face_sw.width = face.width;
	face_sw.height = face.height;
}
