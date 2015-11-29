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
		Scene *scene = new Scene();
		int retriesAvailable = this->retries;
		cv::Point topLeft = cv::Point(-1, -1);
		topLeft = performMatch(scene->getSceneImage());
		while(--retriesAvailable > 0 && (topLeft.x == -1 || topLeft.y == -1)) {
			cout << "Matching template retry: " << retriesAvailable << endl;
			nsleep(retryInterval);
			scene->redraw();
			topLeft = performMatch(scene->getSceneImage());
		}
		return topLeft;
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
			cout << "MinVal: " << minVal << endl;
			topLeft.x = minLoc.x;
			topLeft.y = minLoc.y;
		}
		return topLeft;
	}
#endif