#ifndef Smithing_cpp
#define Smithing_cpp
	#include "Smithing.h"

	Smithing::Smithing() {
		mapButton.reset(new MapButton());
		scene.reset(new Scene());
		dialog.reset(new Dialog());
	}

	Smithing::~Smithing() {

	}

	void Smithing::run() {
		cv::Mat ingot;
		ingot = cv::imread("../images/inventoryItems/MithrilIngot.png");
		unique_ptr<Inventory> inventory(new Inventory());
		inventory->initialize();
		unique_ptr<ImageObject> smeltButton(new ImageObject("../images/SmeltButton.png"));
		unique_ptr<OreSmelter> oreSmelter(new OreSmelter());
		unique_ptr<ArmorDeposit> armorDeposit(new ArmorDeposit());
		unique_ptr<Anvil> anvil(new Anvil());
		while(true) {
			if (inventory->has(ingot)) {
				while(!anvil->use()) {
					nsleep(500);
				}			
				inventory->waitUntilGone(ingot, 3000);
				continue;
			}
			inventory->initialize();
			if (inventory->empty) {
				cout << "Inventory is empty. Using ore smelter." << endl;
				while(!oreSmelter->use()) {
					nsleep(500);
				}			
				if (!smeltButton->waitForMatch()) {
					cout << "Job finished" << endl;
					return;
				}
				smeltButton->clickOn();
				while(!inventory->has(ingot)) {
					nsleep(500);
				}
				continue;
			}
			while(!armorDeposit->use()) {
				nsleep(500);
			}			
			while(!inventory->empty) {
				nsleep(500);
				inventory->initialize();
			}
		}
	}

#endif