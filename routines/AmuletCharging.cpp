#ifndef AmuletCharging_cpp
#define AmuletCharging_cpp
	#include "AmuletCharging.h"

	AmuletCharging::AmuletCharging() {
		bankScreen.reset(new BankScreen());
		chest.reset(new Chest());
		inventory.reset(new Inventory());
		actionBar.reset(new ActionBar());
	}

	AmuletCharging::~AmuletCharging() {

	}

	void AmuletCharging::run(string spellName) {
		vector<cv::Mat> items;
		// items.push_back(cv::imread("../images/inventoryItems/UnchargedDiamondAmulet.png"));
		items.push_back(cv::imread("../images/inventoryItems/DragonstoneNecklace.png"));
		// items.push_back(cv::imread("../images/inventoryItems/DragonstoneRing.png"));
		items.push_back(cv::imread("../images/inventoryItems/DragonstoneBracelet.png"));
		// items.push_back(cv::imread("../images/inventoryItems/SapphireBracelet.png"));
		// items.push_back(cv::imread("../images/inventoryItems/EmeraldRing.png"));
		// items.push_back(cv::imread("../images/inventoryItems/SapphireRing.png"));
		// items.push_back(cv::imread("../images/inventoryItems/RubyBracelet.png"));
		// items.push_back(cv::imread("../images/inventoryItems/EmeraldBracelet.png"));
		map<string, string> spells;
		spells["ENCHANT_DIAMOND_JEWELRY"] = "../images/spells/EnchantDiamondJewelry.png";
		spells["HIGH_LEVEL_ALCHEMY"] = "../images/spells/HighLevelAlchemy.png";
		map<string, int> spellWaitTimes;
		int spellWaitTime = 100;
		spellWaitTimes["HIGH_LEVEL_ALCHEMY"] = 2400;
		if (spellWaitTimes.count(spellName)) {
			spellWaitTime = spellWaitTimes[spellName];
		}
		unique_ptr<ImageObject> spell(new ImageObject(spells[spellName]));
		actionBar->initialize();
		inventory->initialize();
		bool spellInitialized = false;
		while(true) {
			while(!chest->use()) {
				nsleep(500);
			}
			bankScreen->loadPresetOne();
			while(bankScreen->open()) {
				nsleep(500);
			}
			bool found = false;
			for(vector<cv::Mat>::iterator item = items.begin(); item != items.end(); ++item) {
				cout << "SELECT INVENTORY" << endl;
				actionBar->select("Inventory");
				nsleep(1000);
				if (inventory->has(*item)) {
					found = true;
					vector<cv::Point> matches = inventory->getAllMatches(*item);
					actionBar->select("Magic");
					nsleep(200);
					for(vector<cv::Point>::iterator match = matches.begin(); match != matches.end(); ++match) {
						if (!spellInitialized) {
							spell->waitForMatch(100, 4);
							spellInitialized = true;
						}
						spell->clickOn(LEFT_CLICK);
						nsleep(100);
						inventory->clickItem((*match).x, (*match).y, LEFT_CLICK);
						nsleep(spellWaitTime);
					}
				} 
			}
			if (!found) {
				cout << "Job finished" << endl;
				break;
			}
		}
	}

#endif