#ifndef erodefilter_cpp
#define erodefilter_cpp
	#include "ErodeFilter.h"

	ErodeFilter::ErodeFilter() {
		kernelSize = 1;
		erosionType = cv::MORPH_ELLIPSE;
		mode = "ERODE";
	}

	ErodeFilter::~ErodeFilter() {}

	cv::Mat ErodeFilter::apply(cv::Mat in) {
		cv::Mat structuringElem = getStructuringElement( erosionType, cv::Size( 2*kernelSize + 1, 2*kernelSize+1 ), cv::Point( kernelSize, kernelSize ) );
		if (mode == "ERODE") {
			cv::erode(in, in, structuringElem);
		} else {
			cv::dilate(in, in, structuringElem);
		}
		return in;
	}

#endif