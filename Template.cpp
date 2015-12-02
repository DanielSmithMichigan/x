#ifndef template_cpp
#define template_cpp
	#include "Template.h"

	Template::Template(string imageLocation) 
	{
		imgObject = cv::imread(imageLocation, CV_LOAD_IMAGE_COLOR);
		if (!imgObject.data) {
			string error = "Image at this location did not load: " + imageLocation;
			cout << error;
			throw(error);
		}
		retries = 1;
		threshold = .1;
		retryInterval = 200;
		width = imgObject.cols;
		height = imgObject.rows;
		topLeft = cv::Point(-1, -1);
	}

	cv::Mat Template::preprocessImage(cv::Mat &imgIn)
	{
		return imgIn;
	}

	bool Template::match(cv::Mat &imgScene)
	{
		Scene *scene = new Scene();
		int retriesAvailable = this->retries;
		topLeft = performMatch(imgScene);
		while(--retriesAvailable > 0 && (topLeft.x == -1 || topLeft.y == -1)) {
			cout << "Matching template retry: " << retriesAvailable << endl;
			nsleep(retryInterval);
			scene->redraw();
			topLeft = performMatch(imgScene);
		}

		if (topLeft.x == -1 || topLeft.y == -1) {
			return false;
		}
		return true;
	}

	cv::Point Template::performMatch(cv::Mat &imgScene)
	{
		cv::Point topLeft = cv::Point(-1, -1);
		cv::Mat result;
		cv::Mat imgSceneCompare = preprocessImage(imgScene);
		cv::Mat imgObjectCompare = preprocessImage(imgObject);
		matchTemplate(imgSceneCompare, imgObjectCompare, result, CV_TM_SQDIFF_NORMED );
		double minVal, maxVal; 
		cv::Point minLoc, maxLoc;
		minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat() );
		cout << "MinVal: " << minVal << endl;
		if (minVal < threshold) {
			topLeft.x = minLoc.x;
			topLeft.y = minLoc.y;
		}
		return topLeft;
	}
#endif