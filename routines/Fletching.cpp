#ifndef Fletching_cpp
#define Fletching_cpp
	#include "Fletching.h"

	Fletching::Fletching() {

	}

	Fletching::~Fletching() {

	}

	void Fletching::run() {
		unique_ptr<Scene> scene(new Scene());
		unique_ptr<Chest> chest(new Chest());
		unique_ptr<Inventory> inventory(new Inventory());
		unique_ptr<Template> fletchingKnifeTemplate(new Template("../images/FletchKnife.png"));
		fletchingKnifeTemplate->threshold = .01;
		unique_ptr<ImageObject> fletchingKnife(new ImageObject());
		fletchingKnife->addTemplate(move(fletchingKnifeTemplate));
		unique_ptr<ImageObject> fletchingButton(new ImageObject("../images/FletchButton.png"));
		cv::Mat mapleLog = cv::imread("../images/MapleLog.png");

		while(true) {
			inventory->initialize();
			chest->use();
			while(!chest->open()) {
				nsleep(200);
			}
			scene->redraw();
			chest->loadPresetOne();
			nsleep(1000);
			inventory->initialize();
			cv::Point firstLog = inventory->firstMatch(mapleLog);
			if (firstLog.x == -1 || firstLog.y == -1) {
				cout << "Job Finished." << endl;
				return;
			}
			inventory->clickItem(firstLog.x, firstLog.y, LEFT_CLICK);
			nsleep(1000);
			scene->redraw();
			if (fletchingKnife->initialize()) {
				fletchingKnife->clickOn();
				nsleep(2000);
				scene->redraw();
			}
			fletchingButton->initialize();
			fletchingButton->clickOn();
			inventory->initialize();
			cv::Point testPoint = inventory->firstMatch(mapleLog);
			int retries = 0;
			while(testPoint.x > -1 || testPoint.y > -1) {
				inventory->initialize();
				testPoint = inventory->firstMatch(mapleLog);
				nsleep(1000);
				retries++;
				cout << "Retry: " << retries << endl;
			}
		}

	}

#endif