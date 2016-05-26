#ifndef Prayer_cpp
#define Prayer_cpp
	#include "Prayer.h"

	Prayer::Prayer() {

	}

	Prayer::~Prayer() {

	}

	void Prayer::run() {
		unique_ptr<BankScreen> bankScreen(new BankScreen());
		unique_ptr<Scene> scene(new Scene());
		unique_ptr<Chest> chest(new Chest());
		unique_ptr<Inventory> inventory(new Inventory());
		cv::Mat bigBones = cv::imread("../images/inventoryItems/BigBones.png");
		inventory->initialize();
		while(true) {
			while(!chest->use()) {
				cout << "Using chest" << endl;
				nsleep(200);
			}
			bankScreen->waitUntilOpen();
			bankScreen->loadPresetOne();
			while(bankScreen->open()) {
				nsleep(500);
			}
			if (!inventory->has(bigBones)) {
				cout << "Job Finished." << endl;
				return;
			}
			vector<cv::Point> matches = inventory->getAllMatches(bigBones);
			for(vector<cv::Point>::iterator match = matches.begin(); match != matches.end(); ++match) {
				inventory->clickItem((*match).x, (*match).y, LEFT_CLICK);
				nsleep(500);
			}
		}
	}

#endif