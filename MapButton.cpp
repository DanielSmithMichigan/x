#ifndef MapButton_cpp
#define MapButton_cpp
	#include "MapButton.h"

	MapButton::MapButton() {
		rs3 = false;
	}

	MapButton::~MapButton() {

	}

	bool MapButton::initialize() {
		scene->redraw();
		unique_ptr<Template> mapTemplate (new Template(
			rs3? "../images/Rs3WorldMap.png" : "../images/WorldMap.png"
			));
		width = mapTemplate->width;
		height = mapTemplate->height;
	    unique_ptr<ImageObject> worldMap (new ImageObject());
	    worldMap->addTemplate(move(mapTemplate));
	    if (worldMap->initialize()) {
	        topLeft = cv::Point(worldMap->topLeft.x, worldMap->topLeft.y);
	    }
	    Object::initialize();
	}

#endif