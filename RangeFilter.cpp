#ifndef rangefilter_cpp
#define rangefilter_cpp
	#include "RangeFilter.h"

	RangeFilter::RangeFilter() {
		lowHue = 0;
		highHue = 180;
		lowSaturation = 0;
		highSaturation = 255;
		lowValue = 0;
		highValue = 255;
	}

	RangeFilter::~RangeFilter() {}

	cv::Mat RangeFilter::apply(cv::Mat in) {
		cv::cvtColor(in,in,cv::COLOR_BGR2HSV);
		cv::inRange(in, cv::Scalar(lowHue, lowSaturation, lowValue), cv::Scalar(highHue, highSaturation, highValue), in);
		return in;
	}

#endif