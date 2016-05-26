#ifndef GoldSmithing_cpp
#define GoldSmithing_cpp
	#include "GoldSmithing.h"

	GoldSmithing::GoldSmithing() {
		smeltingFurnace.reset(new SmeltingFurnace());
		bankScreen.reset(new BankScreen());
		chest.reset(new Chest("LUMBRIDGE"));
		inventory.reset(new Inventory());
		lumbridgeSmeltingMap.reset(new LumbridgeSmeltingMap());
	}

	GoldSmithing::~GoldSmithing() {

	}

	void GoldSmithing::run() {
		cv::Mat goldOre = cv::imread("../images/inventoryItems/GoldOre.png");
		cv::Mat goldBar = cv::imread("../images/inventoryItems/GoldBar.png");
		cv::Mat cutDragonstone = cv::imread("../images/inventoryItems/CutDragonstone.png");
		vector<cv::Mat> gems;
		gems.push_back(cv::imread("../images/inventoryItems/CutDragonstone.png"));
		inventory->initialize();
		while(true) {
			cout << "Using chest" << endl;
			lumbridgeSmeltingMap->waitUntilInitialize();
			lumbridgeSmeltingMap->goToBank();
			while(!chest->use()) {
				nsleep(500);
				cout << "Going to bank" << endl;
				lumbridgeSmeltingMap->waitUntilInitialize();
				lumbridgeSmeltingMap->goToBank();
			}
			bankScreen->loadPresetOne();
			while(bankScreen->open()) {
				nsleep(500);
			}
			if (!(inventory->has(goldOre) || (inventory->has(goldBar) && inventory->has(cutDragonstone)))) {
				cout << "Job Finished!" << endl;
				break;
			} 
			cout << "Going to furnace" << endl;
			lumbridgeSmeltingMap->waitUntilInitialize();
			lumbridgeSmeltingMap->goToFurnace();
			if (inventory->has(goldOre)) {
				cout << "Have gold ore - Using furnace" << endl;
				while(!smeltingFurnace->use()) {
					nsleep(2000);
					lumbridgeSmeltingMap->waitUntilInitialize();
					lumbridgeSmeltingMap->goToFurnace();
				}
				inventory->waitUntilGone(goldOre);
			}
			if (inventory->has(goldBar)) {
				for(vector<cv::Mat>::iterator it = gems.begin(); it != gems.end(); ++it) {
					if (inventory->has(*it)) {
						cout << "Have gold bar and cut gem, using furnace" << endl;
						while(!smeltingFurnace->use()) {
							nsleep(2000);
							lumbridgeSmeltingMap->waitUntilInitialize();
							lumbridgeSmeltingMap->goToFurnace();
						}
						int retries = 0;
						while(inventory->has(goldBar) && inventory->has(*it)) {
							nsleep(500);
							cout << "Retry: " << retries++ << endl;
						}
					}
				}
			}
		}
	}

#endif