#ifndef cornerfilter_cpp
#define cornerfilter_cpp
	#include "CornerFilter.h"

	CornerFilter::CornerFilter() {
		cornerThreshold = 43;
		blockSize = 2;
		aperture = 3;
		k = .01;

	}

	CornerFilter::~CornerFilter() {}

	cv::Mat CornerFilter::apply(cv::Mat in) {
		cv::Mat out;
  		cv::cvtColor( in, out, cv::COLOR_BGR2GRAY );
  		cv::cornerHarris(out, out, blockSize, aperture, k, cv::BORDER_DEFAULT);
		cv::normalize(out, out, 0, 255, cv::NORM_MINMAX, CV_32FC1);
		cv::convertScaleAbs( out, out );
  		cv::threshold(out, out, cornerThreshold, 255, cv::THRESH_BINARY);
		return out;
	}

#endif