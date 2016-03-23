#ifndef ocrobject_cpp
#define ocrobject_cpp
	#include "OcrObject.h"

	OcrObject::OcrObject() 
	: Object() {
		ocr = cv::text::OCRTesseract::create();
		maxValue = 255;
		threshold = 120;
		minHeight = 40;
		thresholdType = cv::THRESH_BINARY;
	}

	OcrObject::~OcrObject() {
	}

	void OcrObject::initialize() {
	    cv::Mat sceneImage = scene->getSceneImage();
		cv::Mat preparedImage = prepareImage(sceneImage);
		ocr->run(preparedImage, bestGuess);
		// cout << "Best Guess: " << bestGuess << endl;
		Object::initialize();
	}

	cv::Mat OcrObject::prepareImage(cv::Mat &imageIn) {
		cv::Mat imageOut = imageIn(cv::Rect(topLeft.x, topLeft.y, width, height));
		if (height < minHeight) {
			double ratio = minHeight / (double)height;
			int newWidth = ratio * width;
			cv::resize(imageOut, imageOut, cv::Size(newWidth, minHeight), 0, 0, cv::INTER_NEAREST);
		}
		cv::cvtColor(imageOut, imageOut, cv::COLOR_RGB2GRAY);
		cv::threshold(imageOut, imageOut, threshold, maxValue, thresholdType);
		return imageOut;
	}

	bool OcrObject::match(string matchString) {
	    string searchString = bestGuess;
	    searchString.erase(remove_if(searchString.begin(), searchString.end(), ::isspace), searchString.end());
	    searchString = searchString.substr(0, matchString.length());
	    return matchString.compare(searchString) == 0;
	}

#endif