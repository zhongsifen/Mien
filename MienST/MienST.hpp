#pragma once

#include "Mien/Mien.hpp"
#include "StDetect/face_detection.h"
#include "StAlign/face_alignment.h"

class MienST : public Mien
{
	seeta::FaceDetection* fd;
	seeta::FaceAlignment* fa;

	seeta::FaceInfo face_st;
	seeta::FaceLandmark landmark_st;
public:
	MienST();
	~MienST() {

	}

	bool doFace(Gray& gray, Face& face);
	bool doLandmark(Gray & gray, Landmark & landmark);

	bool doChip(Image & image, cv::Rect & r, Chip & chip);
	bool doDesc(Chip & chip, Desc & desc);
	bool doDesc(Image & image, cv::Rect & r, Chip & chip, Desc & desc);

	static void tst(Image & image, seeta::ImageData & image_st);
	static void fst(seeta::FaceLandmark & landmark_st, Landmark & landmark);
};