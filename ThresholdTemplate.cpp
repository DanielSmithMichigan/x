#ifndef thresholdtemplate_cpp
#define thresholdtemplate_cpp
	#include "ThresholdTemplate.h"

	ThresholdTemplate::ThresholdTemplate(string imageLocation) : ImageTemplate(imageLocation) {
		maxValue = 255;
		threshold = 120;
		thresholdType = cv::THRESH_BINARY;
	}

	cv::Mat ThresholdTemplate::preprocessImage(cv::Mat &imageIn) {
		cout << "Converting to threshold image" << endl;
		cv::Mat imageOut;
		cv::cvtColor(imageIn, imageOut, cv::COLOR_RGB2GRAY);
		cv::threshold(imageOut, imageOut, threshold, maxValue, thresholdType);
		return imageOut;
	}

#endif