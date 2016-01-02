#ifndef windowfilter_cpp
#define windowfilter_cpp
	#include "WindowFilter.h"

	WindowFilter::WindowFilter() {
	}

	WindowFilter::~WindowFilter() {}

	cv::Mat WindowFilter::apply(cv::Mat in) {
		cv::Point topLeft;
	    unique_ptr<ImageObject> worldMap (new ImageObject("../images/WorldMap.png"));
	    if (worldMap->initialize()) {
	        topLeft = cv::Point(worldMap->topLeft.x, worldMap->topLeft.y);
	    } else {
	        unique_ptr<ImageObject> helpButton (new ImageObject("../images/HelpButton.png"));
	        if (helpButton->initialize()) {
	            topLeft = cv::Point(helpButton->topLeft.x, helpButton->topLeft.y + 150);
	        } else {
	            string error = "Could not locate map";
	            cout << error << endl;
	            throw(error);
	        }
	    }

	    // left of window
	    cv::rectangle(in, cv::Point(0, 0), cv::Point(topLeft.x - 996, in.rows), CV_RGB(0,0,0), CV_FILLED);

	    // top of window
	    cv::rectangle(in, cv::Point(0, 0), cv::Point(in.cols, topLeft.y - 173), CV_RGB(0,0,0), CV_FILLED);

	    // right of window
	    cv::rectangle(in, cv::Point(topLeft.x + 35, 0), cv::Point(in.cols, in.rows), CV_RGB(0,0,0), CV_FILLED);

	    // below window
	    cv::rectangle(in, cv::Point(0, topLeft.y + 628), cv::Point(in.cols, in.rows), CV_RGB(0,0,0), CV_FILLED);

	    // map
	    cv::rectangle(in, cv::Point(topLeft.x - 206, topLeft.y - 173), cv::Point(topLeft.x + 35, topLeft.y + 61), CV_RGB(0,0,0), CV_FILLED);

	    // inventory
	    cv::rectangle(in, cv::Point(topLeft.x - 206, topLeft.y + 263), cv::Point(topLeft.x + 35, topLeft.y + 628), CV_RGB(0,0,0), CV_FILLED);

	    // chat
	    cv::rectangle(in, cv::Point(topLeft.x - 996, topLeft.y + 436), cv::Point(topLeft.x - 442, topLeft.y + 628), CV_RGB(0,0,0), CV_FILLED);


		return in;
	}

#endif