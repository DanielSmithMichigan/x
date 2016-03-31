#ifndef Crafting_cpp
#define Crafting_cpp
	#include "Crafting.h"

	Crafting::Crafting() {
		scene.reset(new Scene());
		inventory.reset(new Inventory());
		rock.reset(new Rock());
		pottersWheel.reset(new PottersWheel());
		sink.reset(new Sink());
		craftingFurnace.reset(new CraftingFurnace());
		craftingGuildWaterSymbol.reset(new CraftingGuildWaterSymbol());
	    clay = cv::imread("../images/inventoryItems/Clay.png");
	    softClay = cv::imread("../images/inventoryItems/SoftClay.png");
	    firedUrn = cv::imread("../images/inventoryItems/FiredUrn.png");
	    unfiredUrn = cv::imread("../images/inventoryItems/UnfiredUrn.png");
	    dontDrop.push_back(clay);
	    dontDrop.push_back(softClay);
	    dontDrop.push_back(unfiredUrn);
	}

	Crafting::~Crafting() {

	}

	void Crafting::run() {

		while(true) {
			inventory->initialize();
			if (inventory->has(unfiredUrn)) {
				cout << "Using Furnace" << endl;
				while(!craftingFurnace->use()) {
					cout << "Could not find furnace. Going to center of crafting guild" << endl;
					while (!craftingGuildWaterSymbol->initialize()) {
						nsleep(500);
					}
					craftingGuildWaterSymbol->goToCraftingGuildCenter();
				}
		        inventory->waitUntilGone(unfiredUrn);
				inventory->dropAllItems();
			}
			if (!inventory->full) {
				cout << "Mining Clay" << endl;
				while(!craftingGuildWaterSymbol->initialize()) {
					nsleep(250);
				}
				craftingGuildWaterSymbol->goToMinesite();
				while(!inventory->full) {
					rock->use("CLAY");
					inventory->waitForItem();
					inventory->dropEverythingBut(dontDrop);
					inventory->initialize();
				}
			}
			if (inventory->has(clay)) {
				cout << "Using sink" << endl;
				while(!sink->use()) {
					cout << "Could not find sink. Clicking water symbol" << endl;
					while (!craftingGuildWaterSymbol->initialize()) {
						nsleep(500);
					}
					craftingGuildWaterSymbol->goToCraftingGuildCenter();
				}
				inventory->waitUntilGone(clay);
			}
			if (inventory->countItem(softClay) > 1) {
				cout << "Using Potter's Wheel" << endl;
				while(!pottersWheel->use()) {
					cout << "Could not find potters wheel. Going to center of crafting guild" << endl;
					while (!craftingGuildWaterSymbol->initialize()) {
						nsleep(500);
					}
					craftingGuildWaterSymbol->goToCraftingGuildCenter();
				}
				int count = 0;
		        while(inventory->countItem(softClay) > 1) {
		        	cout << "Retry: " << ++count << endl;
		        	nsleep(1000);
		        }
			}
        }
	}

#endif