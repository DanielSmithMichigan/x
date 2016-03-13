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
		unique_ptr<ImageObject> smeltButton(new ImageObject("../images/SmeltButton.png"));
		unique_ptr<OreSmelter> oreSmelter(new OreSmelter());
		unique_ptr<ArmorDeposit> armorDeposit(new ArmorDeposit());
		unique_ptr<Anvil> anvil(new Anvil());

		while(true) {
			scene->redraw();
			oreSmelter->use();
			scene->redraw();
			smeltButton->initialize();
			smeltButton->clickOn();
			nsleep(500);
			scene->redraw();
			anvil->use();
			inventory->initialize();
			cv::Point testPoint = inventory->firstMatch(ingot);
			int retries = 0;
			while(testPoint.x > -1 || testPoint.y > -1) {
				inventory->initialize();
				testPoint = inventory->firstMatch(ingot);
				nsleep(10000);
				retries++;
				cout << "Retry: " << retries << endl;
			}
			armorDeposit->use();
		}
	}

#endif