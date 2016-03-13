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
	}

	Crafting::~Crafting() {

	}

	void Crafting::run() {
		if (inventory->has(firedUrn)) {
			inventory->dropAllItems();
		}
		while(true) {
			inventory->initialize();
			if (inventory->has(unfiredUrn)) {
				cout << "Using Furnace" << endl;
				while(!craftingFurnace->use()) {
					cout << "Could not find sink. Going to center of crafting guild" << endl;
					craftingGuildWaterSymbol->initialize();
					craftingGuildWaterSymbol->goToCraftingGuildCenter();
				}
		        inventory->waitUntilGone(unfiredUrn);
				inventory->dropAllItems();
			}
			if (!inventory->full) {
				cout << "Mining Clay" << endl;
				craftingGuildWaterSymbol->initialize();
				craftingGuildWaterSymbol->goToMinesite();
				while(!inventory->full) {
					rock->use("CLAY");
					inventory->waitForItem();
				}
			}
			if (inventory->has(clay)) {
				cout << "Using sink" << endl;
				while(!sink->use()) {
					cout << "Could not find sink. Clicking water symbol" << endl;
					craftingGuildWaterSymbol->initialize();
					craftingGuildWaterSymbol->clickOn(LEFT_CLICK);
					nsleep(5000);
					scene->redraw();
				}
				inventory->waitUntilGone(clay);
			}
			if (inventory->has(softClay)) {
				cout << "Using Potter's Wheel" << endl;
				while(!pottersWheel->use()) {
					cout << "Could not find potters wheel. Going to center of crafting guild" << endl;
					craftingGuildWaterSymbol->initialize();
					craftingGuildWaterSymbol->goToCraftingGuildCenter();
				}
		        inventory->waitUntilGone(softClay);
			}
        }
	}

#endif