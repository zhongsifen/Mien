// Copyright (C) 2011  Davis E. King (davis@dlib.net), Nils Labugt, Changjiang Yang (yangcha@leidos.com)
// License: Boost Software License   See LICENSE.txt for the full license.
#ifndef DLIB_LOAd_IMAGE_Hh_
#define DLIB_LOAd_IMAGE_Hh_

#include <opencv2/opencv.hpp>
#include "dlib/opencv.h"

namespace dlib
{
	template <typename image_type>
	void load_image(
		image_type& image,
		const std::string& file_name
	)
	{
		cv::Mat img =	cv::imread(file_name);
		assign_image(image, cv_image<bgr_pixel>(img));
	}
}

#endif // DLIB_LOAd_IMAGE_Hh_ 
