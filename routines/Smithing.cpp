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
			while(!oreSmelter->use()) {
				nsleep(500);
			}			
			smeltButton->waitForMatch();
			smeltButton->clickOn();
			scene->redraw();
			while(!anvil->use()) {
				nsleep(500);
			}			
			inventory->waitUntilGone(ingot, 3000);
			while(!armorDeposit->use()) {
				nsleep(500);
			}			
		}
	}

#endif