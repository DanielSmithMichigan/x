#ifndef skillchompahunting_cpp
#define skillchompahunting_cpp
	#include "SkillChompaHunting.h"

	SkillChompaHunting::SkillChompaHunting() {
		inventory.reset(new Inventory());
		interfaceMap.reset(new Map());
		boxTrap.reset(new BoxTrap());
	}

	SkillChompaHunting::~SkillChompaHunting() {

	}

	void SkillChompaHunting::run() {
        // interfaceMap->initialize();
        inventory->initialize();
        // cv::Mat boxTrap = cv::imread("../images/inventoryItems/boxTrap.png");
        // cv::Point match = inventory->firstMatch(boxTrap);
        // inventory->clickItem(match.x, match.y, RIGHT_CLICK);
        boxTrap->use();
	}

#endif