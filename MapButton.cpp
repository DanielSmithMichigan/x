#ifndef MapButton_cpp
#define MapButton_cpp
	#include "MapButton.h"

	MapButton::MapButton() {
	}

	MapButton::~MapButton() {

	}

	bool MapButton::initialize() {
		unique_ptr<Template> mapTemplate (new Template("../images/WorldMap.png"));
		width = mapTemplate->width;
		height = mapTemplate->height;
	    unique_ptr<ImageObject> worldMap (new ImageObject());
	    worldMap->addTemplate(move(mapTemplate));
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
	    Object::initialize();
	}

#endif