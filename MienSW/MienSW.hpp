#pragma once

#include "Mien/Mien.hpp"
#include <seeta/FaceDetector2.h>
#include <seeta/PointDetector2.h>
#include <seeta/FaceRecognizer.h>

#include <seeta/Struct_cv.h>
#include <opencv2/opencv.hpp>

#pragma comment(lib, "SeetaFaceDetector200.lib")
#pragma comment(lib, "SeetaPointDetector200.lib")
#pragma comment(lib, "SeetaFaceRecognizer200.lib")

class MienSW : public Mien {
protected:
	seeta::FaceDetector2* FD;
	seeta::PointDetector2* PD;
	seeta::FaceRecognizer2* FR;

public:
	MienSW();
	~MienSW() { FR->Clear(); };

	bool doFace(Image & imageGray, Face& face);
	bool doLandmark(Image & image, Face & face, Landmark & landmark);
	bool doChip(Image & image, cv::Rect & r, Chip & chip);
	bool doDesc(Chip & chip, Desc & desc);
	bool doDesc(Image & image, cv::Rect & r, Chip & chip, Desc & desc);

	static void fsw(SeetaRect & face_sw, Face & face);
	static void fsw(SeetaPointF landmark_sw[], Landmark & landmark);
	static void tsw(Face & face, SeetaRect & face_sw);
};
