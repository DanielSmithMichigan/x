#ifndef AmuletStringing_cpp
#define AmuletStringing_cpp
	#include "AmuletStringing.h"

	AmuletStringing::AmuletStringing() {
		bankScreen.reset(new BankScreen());
		chest.reset(new Chest());
		inventory.reset(new Inventory());
		actionButton.reset(new ActionButton());
	}

	AmuletStringing::~AmuletStringing() {

	}

	void AmuletStringing::run() {
		cv::Mat unstrungDiamondAmulet = cv::imread("../images/inventoryItems/UnstrungYewShieldBow.png");
		cv::Mat ballOfWool = cv::imread("../images/inventoryItems/BowString.png");
		inventory->initialize();
		while(true) {
			while(!chest->use()) {
				nsleep(500);
			}
			bankScreen->loadPresetOne();
			while(bankScreen->open()) {
				nsleep(500);
			}
			if (!inventory->has(ballOfWool) || !inventory->has(unstrungDiamondAmulet)) {
				cout << "Job Finished!" << endl;
				break;
			} 
			cv::Point ballOfWoolInv = inventory->firstMatch(ballOfWool);
			cv::Point unstrungDiamondAmuletInv = inventory->firstMatch(unstrungDiamondAmulet);
			inventory->clickItem(ballOfWoolInv.x, ballOfWoolInv.y, LEFT_CLICK);
			inventory->clickItem(unstrungDiamondAmuletInv.x, unstrungDiamondAmuletInv.y, LEFT_CLICK);
			actionButton->waitForMatch();
			actionButton->clickOn(LEFT_CLICK);
			int retries = 0;
			while(inventory->has(unstrungDiamondAmulet) && inventory->has(ballOfWool)) {
				nsleep(500);
				cout << "Retry: " << retries++ << endl;
			}
		}
	}

#endif