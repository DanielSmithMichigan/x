#ifndef template_cpp
#define template_cpp
	#include "Template.h"

	Template::Template(cv::Mat &imgObject) 
	:imgObject(imgObject) {
		retries = 5;
		threshold = .2;
		retryInterval = 200;
	}

	cv::Point Template::match(cv::Mat &imgScene)
	{
		int retriesAvailable = this->retries;
		cv::Point topLeft = cv::Point(-1, -1);
		while(retriesAvailable-- > 0 && (topLeft.x == -1 || topLeft.y == -1)) {
			topLeft = performMatch(imgScene);
		}
	}

	cv::Point Template::performMatch(cv::Mat &imgScene)
	{
		cv::Point topLeft = cv::Point(-1, -1);
		cv::Mat result;
		matchTemplate(imgScene, imgObject, result, CV_TM_SQDIFF_NORMED );
		double minVal, maxVal; 
		cv::Point minLoc, maxLoc;
		minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat() );
		if (minVal < threshold) {
			topLeft.x = minLoc.x;
			topLeft.y = minLoc.y;
		}
		return topLeft;
	}
#endif