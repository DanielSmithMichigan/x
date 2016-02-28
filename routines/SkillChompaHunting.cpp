#ifndef skillchompahunting_cpp
#define skillchompahunting_cpp
	#include "SkillChompaHunting.h"

	SkillChompaHunting::SkillChompaHunting() {
		inventory.reset(new Inventory());
		interfaceMap.reset(new Map());
		boxTrap.reset(new BoxTrap());
		dialog.reset(new Dialog());
		hunterIcon.reset(new ImageObject("../images/HunterIcon.png"));
		scene.reset(new Scene());
		huntingLocations.push(cv::Point(25, 0));
		huntingLocations.push(cv::Point(37, 0));
		huntingLocations.push(cv::Point(25, 5));
		huntingLocations.push(cv::Point(37, 5));
	}

	SkillChompaHunting::~SkillChompaHunting() {

	}

	void SkillChompaHunting::run() {
        inventory->initialize();
        cv::Mat boxTrapItem = cv::imread("../images/inventoryItems/boxTrap.png");
        while(true) {
        	if (boxTrap->use()) {
        		continue;
        	}
        	cv::Point match = inventory->firstMatch(boxTrapItem);
        	if (match.x != -1 && match.y != -1) {
        		if (gotoNextLocation()) {
	        		nsleep(2500);
        		}
        		inventory->clickItem(match.x, match.y, RIGHT_CLICK);
		        dialog->initialize();
		        if (dialog->select("Lay")) {
		        	nsleep(4500);
		        	continue;
		        } else {
		        	dialog->select("Cancel");
		        }
        	}
        }
	}

	bool SkillChompaHunting::gotoNextLocation() {
    	cv::Point nextLocation = getNextLocation();
    	if (nextLocation.x == -1
    		|| nextLocation.y == -1) {
    		return false;
    	}
    	glideToPosition(nextLocation.x, nextLocation.y);
    	click(LEFT_CLICK);
    	return true;
	}

	cv::Point SkillChompaHunting::getNextLocation() {
		scene->redraw();
		hunterIcon->initialize();
		if (hunterIcon->topLeft.x == -1
			|| hunterIcon->topLeft.y == -1) {
			return cv::Point(-1, -1);
		}
		cv::Point next = huntingLocations.front();
		huntingLocations.pop();
		huntingLocations.push(next);
		cout << "GOING TO: " << next << endl;
		return cv::Point(hunterIcon->topLeft.x + next.x, hunterIcon->topLeft.y + next.y);
	}

#endif