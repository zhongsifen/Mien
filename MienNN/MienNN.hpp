#pragma once

#include "Mien/Mien.hpp"
#include "mtcnn/mtcnn.h"

class Mnn : mtcnn
{
public:
	Mnn(int rows, int cols) { setup(rows, cols); }
	bool doEEM(Mien::Image & image, Mien::Face & face, Mien::EEM & eem);
};

class MienNN : Mien
{
	Mnn* nn;
public:
	bool setup(int rows, int cols);
	bool doEEM(Mien::Image & image, Mien::Face & face, Mien::EEM & eem);
};
