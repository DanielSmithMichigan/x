#ifndef template_cpp
#define template_cpp
	#include "Template.h"

	Template::Template(string imageLocation) 
	: Template()
	{
		imgObject = cv::imread(imageLocation, CV_LOAD_IMAGE_COLOR);
		if (!imgObject.data) {
			string error = "Image at this location did not load: " + imageLocation;
			cout << error;
			throw(error);
		}
		width = imgObject.cols;
		height = imgObject.rows;
	}

	Template::Template(cv::Mat i) : Template() {
		imgObject = i;
		width = imgObject.cols;
		height = imgObject.rows;
	}

	Template::Template() 
	{
		retries = 1;
		retryInterval = 200;
		width = -1;
		height = -1;
		rotation = 0;
		scaling = 1; 
		topLeft = cv::Point(-1, -1);
		unique_ptr<Scene> scene (new Scene());
		threshold = .15;
		logFailure = false;
	}

	cv::Mat Template::preprocessImage(cv::Mat &imgIn, string imageName)
	{
		return imgIn;
	}

	Template::~Template() {

	}

	bool Template::match(cv::Mat &sceneImage)
	{
		int retriesAvailable = this->retries;
		topLeft = performMatch(sceneImage);
		while(--retriesAvailable > 0 && (topLeft.x == -1 || topLeft.y == -1)) {
			cout << "Matching template retry: " << retriesAvailable << endl;
			prepareForRetry();
			topLeft = performMatch(sceneImage);
		}

		if (topLeft.x == -1 || topLeft.y == -1) {
			return false;
		}
		
		return true;
	}

	void Template::prepareForRetry()
	{
		nsleep(retryInterval);
		scene->redraw();
	}

	cv::Point Template::performMatch(cv::Mat &imgScene)
	{
		cv::Point topLeft = cv::Point(-1, -1);
		cv::Mat result;
		cv::Mat imgSceneCompare = preprocessImage(imgScene, "SCENE");
		cv::Mat imgObjectCompare = preprocessImage(imgObject, "OBJECT");
		matchTemplate(imgSceneCompare, imgObjectCompare, result, CV_TM_SQDIFF_NORMED );
		double minVal, maxVal; 
		cv::Point minLoc, maxLoc;
		minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat() );
		cout << "MinVal: " << minVal << endl;
		if (minVal < threshold) {
			topLeft.x = minLoc.x;
			topLeft.y = minLoc.y;
		} else if (logFailure) {
			cout << "Could not find template in image" << endl;
			string numString = to_string(randomBetween(1000, 9999));
			cv::imwrite("../log/Template" + numString + ".png", scene->getSceneImage());
		}
		return topLeft;
	}

#endif