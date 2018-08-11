#pragma once

#include "Mien/Mien.hpp"
#include "mtcnn/mtcnn.h"

class Mnn : public mtcnn
{
public:
	Mnn(int rows, int cols) { setup(rows, cols); }
	bool doLandmark(Mien::Image & image, Mien::Face & face, Mien::Landmark & langmark);
};

class MienNN : Mien
{
	Mnn* nn;
public:
	bool setup(int rows, int cols);
	bool doLandmark(Mien::Image & image, Mien::Face & face, Mien::Landmark & landmark);

	static void fnn(Bbox & bboxs, Mien::Face & face, Mien::Landmark & landmark);
};
