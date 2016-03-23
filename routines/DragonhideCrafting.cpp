#ifndef DragonhideCrafting_cpp
#define DragonhideCrafting_cpp
	#include "DragonhideCrafting.h"

	DragonhideCrafting::DragonhideCrafting() {

	}

	DragonhideCrafting::~DragonhideCrafting() {

	}

	void DragonhideCrafting::run() {
		unique_ptr<Scene> scene(new Scene());
		unique_ptr<Chest> chest(new Chest());
		unique_ptr<Inventory> inventory(new Inventory());
		unique_ptr<Template> needleTemplate(new Template("../images/Needle.png"));
		needleTemplate->threshold = .01;
		unique_ptr<ImageObject> needle(new ImageObject());
		needle->addTemplate(move(needleTemplate));
		unique_ptr<ImageObject> leatherworkButton(new ImageObject("../images/LeatherworkButton.png"));
		cv::Mat greenDragonhideLeather = cv::imread("../images/inventoryItems/GreenDragonhideLeather.png");

		while(true) {
			inventory->initialize();
			while(!chest->use()) {
				cout << "Using chest" << endl;
				nsleep(200);
			}
			while(!chest->open()) {
				nsleep(200);
			}
			scene->redraw();
			chest->loadPresetOne();
			while(chest->open()) {
				nsleep(200);
			}
			if (!inventory->has(greenDragonhideLeather)) {
				cout << "Job Finished." << endl;
				return;
			}
			cv::Point firstLeather = inventory->firstMatch(greenDragonhideLeather);
			inventory->clickItem(firstLeather.x, firstLeather.y, LEFT_CLICK);
			if (needle->waitForMatch(2)) {
				needle->clickOn();
			}
			leatherworkButton->waitForMatch();
			leatherworkButton->clickOn();
			inventory->waitUntilGone(greenDragonhideLeather);
		}

	}

#endif