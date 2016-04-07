#ifndef GoldSmithing_cpp
#define GoldSmithing_cpp
	#include "GoldSmithing.h"

	GoldSmithing::GoldSmithing() {
		smeltingFurnace.reset(new SmeltingFurnace());
		bankScreen.reset(new BankScreen());
		chest.reset(new Chest());
		inventory.reset(new Inventory());
		lumbridgeSmeltingMap.reset(new LumbridgeSmeltingMap());
	}

	GoldSmithing::~GoldSmithing() {

	}

	void GoldSmithing::run() {
		cv::Mat goldOre = cv::imread("../images/inventoryItems/GoldOre.png");
		cv::Mat goldBar = cv::imread("../images/inventoryItems/GoldBar.png");
		cv::Mat cutDiamond = cv::imread("../images/inventoryItems/CutDiamond.png");
		inventory->initialize();
		while(true) {
			cout << "Initializing map" << endl;
			while(!lumbridgeSmeltingMap->initialize()) {
				nsleep(500);
			}
			cout << "Going to bank" << endl;
			lumbridgeSmeltingMap->goToBank();
			cout << "Using chest" << endl;
			while(!chest->use()) {
				nsleep(500);
			}
			while(!bankScreen->open()) {
				nsleep(500);
			}
			bankScreen->loadPresetOne();
			while(bankScreen->open()) {
				nsleep(500);
			}
			if (!inventory->has(goldOre) || !inventory->has(cutDiamond)) {
				cout << "Job Finished!" << endl;
				break;
			} 
			cout << "Initializing map" << endl;
			while(!lumbridgeSmeltingMap->initialize()) {
				nsleep(500);
			}
			cout << "Going to furnace" << endl;
			lumbridgeSmeltingMap->goToFurnace();
			if (inventory->has(goldOre)) {
				cout << "Have gold ore - Using furnace" << endl;
				smeltingFurnace->use();
				inventory->waitUntilGone(goldOre);
			}
			if (inventory->has(goldBar) && inventory->has(cutDiamond)) {
				cout << "Have gold bar and cut diamond, using furnace" << endl;
				smeltingFurnace->use();
				int retries = 0;
				while(inventory->has(goldBar) || inventory->has(cutDiamond)) {
					nsleep(500);
					cout << "Retry: " << retries++ << endl;
				}
			}
		}
	}

#endif