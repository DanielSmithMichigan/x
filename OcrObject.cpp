#ifndef ocrobject_cpp
#define ocrobject_cpp
	#include "OcrObject.h"

	OcrObject::OcrObject() 
	: Object() {
		ocr = cv::text::OCRTesseract::create();
		maxValue = 255;
		threshold = 120;
		minHeight = 40;
		simstringThreshold = .95;
		thresholdType = cv::THRESH_BINARY;
	}

	OcrObject::~OcrObject() {
	}

	void OcrObject::initialize() {
		cout << "Initializing" << endl;
	    dbr.open("../simstring/words.db");
	    cv::Mat sceneImage = scene->getSceneImage();
		cv::Mat preparedImage = prepareImage(sceneImage);
		ocr->run(preparedImage, bestGuess);
		cout << "Best Guess: " << bestGuess << endl;
		Object::initialize();
	}

	cv::Mat OcrObject::prepareImage(cv::Mat &imageIn) {
		cv::Mat imageOut = imageIn(cv::Rect(topLeft.x, topLeft.y, width, height));
		if (height < minHeight) {
			double ratio = minHeight / (double)height;
			cout << "Resizing with ratio: " << ratio << endl;
			int newWidth = ratio * width;
			cv::resize(imageOut, imageOut, cv::Size(newWidth, minHeight), 0, 0, cv::INTER_NEAREST);
		}
		cv::cvtColor(imageOut, imageOut, cv::COLOR_RGB2GRAY);
		cv::threshold(imageOut, imageOut, threshold, maxValue, thresholdType);
		return imageOut;
	}

	bool OcrObject::match(string matchString) {
		cout << "Matching against: " << matchString << endl;
	    std::vector<std::string> matches;
	    string searchString = bestGuess;
	    searchString.erase(std::remove_if(searchString.begin(), searchString.end(), ::isspace), searchString.end());
	    searchString = searchString.substr(0, matchString.length());
	    cout << "Searching database for " << searchString << endl;
	    dbr.retrieve(searchString, simstring::cosine, simstringThreshold, std::back_inserter(matches));
	    cout << "Number of matches: " << matches.size() << endl;
		for(std::vector<string>::iterator iter = matches.begin(); iter != matches.end(); ++iter) {
			cout << "Checking match: " << *iter << endl;
		}
	    return find(matches.begin(), matches.end(), matchString) != matches.end();
	}

#endif