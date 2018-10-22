#pragma once

#include "Mien/Mien.hpp"
#include "SeetaFace/face_detection.h"
#include "SeetaFace/face_alignment.h"
#include "SeetaFace/face_identification.h"

class MienST : public Mien
{
	seeta::FaceDetection* fd;
	seeta::FaceAlignment* fa;
	seeta::FaceIdentification* fr;

	seeta::FaceInfo face_st;
	seeta::FaceLandmark landmark_st;
public:
	enum {
		NONE,
		INIT,
		FACE,
		LANDMARK,
		CHIP,
	} stage;

	MienST();
	~MienST() {}

	bool init();
	bool doFace(Gray& gray, Face& face);
	bool doLandmark(Gray & gray, Landmark & landmark);
	bool doChip(Image & image, Chip & chip);

	bool doDesc(Chip & chip, Desc & desc);
	bool doDesc(Image & image, cv::Rect & r, Chip & chip, Desc & desc);

	static void tst(Image & image, seeta::ImageData & image_st);
	static void fst(seeta::FaceLandmark & landmark_st, Landmark & landmark);
};
