#pragma once

#include "Mien/Mien.hpp"
#include "mtcnn/mtcnn.h"

class Mnn : mtcnn
{
public:
	Mnn(int rows, int cols) { mtcnn(rows, cols); }
	bool doLandmark(Mien::Image & image, Mien::Face & face, Mien::EEM & eem);
};

class MienNN : Mien
{
	Mnn* nn;
public:
	setup(int rows, int cols);
};
