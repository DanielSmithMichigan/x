#ifndef Fletching_cpp
#define Fletching_cpp
	#include "Fletching.h"

	Fletching::Fletching() {

	}

	Fletching::~Fletching() {

	}

	void Fletching::run() {
		unique_ptr<BankScreen> bankScreen(new BankScreen());
		unique_ptr<Scene> scene(new Scene());
		unique_ptr<Chest> chest(new Chest());
		unique_ptr<Inventory> inventory(new Inventory());
		unique_ptr<Template> fletchingKnifeTemplate(new Template("../images/FletchKnife.png"));
		fletchingKnifeTemplate->threshold = .01;
		unique_ptr<ImageObject> fletchingKnife(new ImageObject());
		fletchingKnife->addTemplate(move(fletchingKnifeTemplate));
		unique_ptr<ImageObject> fletchingButton(new ImageObject("../images/FletchButton.png"));
		cv::Mat mapleLog = cv::imread("../images/MapleLog.png");
		inventory->initialize();
		while(true) {
			while(!chest->use()) {
				cout << "Using chest" << endl;
				nsleep(200);
			}
			while(!bankScreen->open()) {
				nsleep(200);
			}

			while(bankScreen->open()) {
				bankScreen->loadPresetOne();
				nsleep(1000);
			}
			if (!inventory->has(mapleLog)) {
				cout << "Job Finished." << endl;
				return;
			}
			cv::Point firstLog = inventory->firstMatch(mapleLog);
			inventory->clickItem(firstLog.x, firstLog.y, LEFT_CLICK);
			if (fletchingKnife->waitForMatch(4)) {
				fletchingKnife->clickOn();
			}
			fletchingButton->waitForMatch();
			fletchingButton->clickOn();
			inventory->waitUntilGone(mapleLog);
		}

	}

#endif