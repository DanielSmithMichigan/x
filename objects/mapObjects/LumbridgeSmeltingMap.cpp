#ifndef LumbridgeSmeltingMap_cpp
#define LumbridgeSmeltingMap_cpp
	#include "LumbridgeSmeltingMap.h"

	LumbridgeSmeltingMap::LumbridgeSmeltingMap() {
		map.reset(new Map());
	}

	LumbridgeSmeltingMap::~LumbridgeSmeltingMap() {
	}

	bool LumbridgeSmeltingMap::initialize()
	{
		map->initialize();
		scene->redraw();
		topLeft.x = -1; topLeft.y = -1;
		unique_ptr<Template> dollarIconTemplate(new Template("../images/mapObjects/dollarIcon.png"));
		dollarIconTemplate->threshold = .025;
	    unique_ptr<ImageObject> dollarIcon (new ImageObject());
	    dollarIcon->addTemplate(move(dollarIconTemplate));


		unique_ptr<Template> potIconTemplate(new Template("../images/mapObjects/potIcon.png"));
		potIconTemplate->threshold = .025;
	    unique_ptr<ImageObject> potIcon (new ImageObject());
	    potIcon->addTemplate(move(potIconTemplate));


		unique_ptr<Template> arrowIconTemplate(new Template("../images/mapObjects/arrowIcon.png"));
		arrowIconTemplate->threshold = .025;
	    unique_ptr<ImageObject> arrowIcon (new ImageObject());
	    arrowIcon->addTemplate(move(arrowIconTemplate));


		unique_ptr<Template> fishIconTemplate(new Template("../images/mapObjects/fishIcon.png"));
		fishIconTemplate->threshold = .025;
	    unique_ptr<ImageObject> fishIcon (new ImageObject());
	    fishIcon->addTemplate(move(fishIconTemplate));

		unique_ptr<Template> furnaceIconTemplate(new Template("../images/mapObjects/furnaceIcon.png"));
		furnaceIconTemplate->threshold = .025;
	    unique_ptr<ImageObject> furnaceIcon (new ImageObject());
	    furnaceIcon->addTemplate(move(furnaceIconTemplate));

	    if (topLeft.x == -1 || topLeft.y == -1) {
	        if (furnaceIcon->initialize()) {
	            topLeft = cv::Point(furnaceIcon->topLeft.x - 52, furnaceIcon->topLeft.y - 4);
			    width = furnaceIcon->width;
			    height = furnaceIcon->height;
	        }
	    }

	    if (topLeft.x == -1 || topLeft.y == -1) {
		    if (dollarIcon->initialize()) {
		        topLeft = cv::Point(dollarIcon->topLeft.x, dollarIcon->topLeft.y);
			    width = dollarIcon->width;
			    height = dollarIcon->height;
		    } 
		}

	    if (topLeft.x == -1 || topLeft.y == -1) {
	        if (potIcon->initialize()) {
	            topLeft = cv::Point(potIcon->topLeft.x, potIcon->topLeft.y  - 54);
			    width = potIcon->width;
			    height = potIcon->height;
	        }
	    }

	    if (topLeft.x == -1 || topLeft.y == -1) {
	        if (arrowIcon->initialize()) {
	            topLeft = cv::Point(arrowIcon->topLeft.x - 65, arrowIcon->topLeft.y - 12);
			    width = arrowIcon->width;
			    height = arrowIcon->height;
	        }
	    }

	    if (topLeft.x == -1 || topLeft.y == -1) {
	        if (fishIcon->initialize()) {
	            topLeft = cv::Point(fishIcon->topLeft.x - 88, fishIcon->topLeft.y - 16);
			    width = fishIcon->width;
			    height = fishIcon->height;
	        }
	    }

	    if (topLeft.x != -1 && topLeft.y != -1) {
	    	Object::initialize();
	    	return true;
	    }
	    return false;
	} 

	bool LumbridgeSmeltingMap::waitUntilInitialize() {
		while(!initialize()) {
			nsleep(500);
		}
		return true;
	}
	void LumbridgeSmeltingMap::goToBank()
	{
		glideToPosition(topLeft.x, topLeft.y);
		click(LEFT_CLICK);
		map->waitDuringMovement();
	}
	void LumbridgeSmeltingMap::goToFurnace()
	{
		glideToPosition(topLeft.x + 50, topLeft.y + 20);
		click(LEFT_CLICK);
		map->waitDuringMovement();
	}
#endif