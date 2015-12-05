#ifndef imagetemplate_cpp
#define imagetemplate_cpp
	#include "ImageTemplate.h"

	ImageTemplate::ImageTemplate(string imageLocation) 
	: Template()
	{
		imgObject = cv::imread(imageLocation, CV_LOAD_IMAGE_COLOR);
		if (!imgObject.data) {
			string error = "Image at this location did not load: " + imageLocation;
			cout << error;
			throw(error);
		}
		threshold = .1;
		width = imgObject.cols;
		height = imgObject.rows;
	}

	cv::Mat ImageTemplate::preprocessImage(cv::Mat &imgIn)
	{
		return imgIn;
	}

	void ImageTemplate::prepareForRetry()
	{
		nsleep(retryInterval);
		scene->redraw();
	}

	cv::Point ImageTemplate::performMatch(cv::Mat &imgScene)
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