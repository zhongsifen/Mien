//
//  MienX.cpp
//  Mien58
//
//  Created by SIFEN ZHONG on 4/10/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "MienDL.hpp"
#include "dlib_cv.hpp"
#include <opencv2/imgproc.hpp>

using namespace cv;

namespace MienX {
	void getSimTransform(const std::vector<Point2f>& pt_src, const std::vector<Point2f> pt_dst, Matx23d& aff)
	{
		Point2f s = pt_src[1] - pt_src[0];
		Point2f d = pt_dst[1] - pt_dst[0];
		double s_norm = norm(s);
		double d_norm = norm(d);
		double alpha = d_norm / s_norm;
		
		double cs = (Mat(s).dot(Mat(d)))/(s_norm*d_norm);
		double sn = sqrt(1 - cs*cs);
		
		cs *= alpha;
		sn *= alpha;
		
		Point2f s0 = pt_src[0];
		Point2f d0 = pt_dst[0];
		
		Point2f b = d0 - Point2f((float)(+cs*s0.x +sn*s0.y), (float)(-sn*s0.x +cs*s0.y));
		
		aff = Matx23d(+cs, +sn, b.x, -sn, +cs, b.y);
	}
	
	bool align(cv::Mat& f, std::vector<Point2f>& pt_src, const std::vector<Point2f> pt_dst, cv::Size _box, cv::Mat& h) {
		Matx23d aff;
		getSimTransform(pt_src, pt_dst, aff);
		warpAffine(f, h, aff, _box);
		
		return true;
	}
}
