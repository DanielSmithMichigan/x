#ifndef ShiftFilter_cpp
#define ShiftFilter_cpp
	#include "ShiftFilter.h"

	ShiftFilter::ShiftFilter() {
		offsetX = 0;
		offsetY = 0;
	}

	ShiftFilter::~ShiftFilter() {}

	cv::Mat ShiftFilter::apply(cv::Mat in) {
	    cv::Mat translationMatrix = (cv::Mat_<double>(2,3) << 1, 0, offsetX, 0, 1, offsetY);
	    cv::warpAffine(in,in,translationMatrix,in.size());
	    return in;
	}

#endif