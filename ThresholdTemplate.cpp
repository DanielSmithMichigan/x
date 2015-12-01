#ifndef thresholdtemplate_cpp
#define thresholdtemplate_cpp
	#include "ThresholdTemplate.h"

	ThresholdTemplate::ThresholdTemplate(string imageLocation) : Template(imageLocation) {
		this->maxValue = 255;
		this->threshold = 120;
		this->thresholdType = cv::THRESH_BINARY;
	}

	cv::Mat ThresholdTemplate::preprocessImage(cv::Mat &imageIn) {
		cout << "Converting to threshold image" << endl;
		cv::Mat imageOut;
		cv::cvtColor(imageIn, imageOut, cv::COLOR_RGB2GRAY);
		cv::threshold(imageOut, imageOut, this->threshold, this->maxValue, this->thresholdType);
		return imageOut;
	}

#endif