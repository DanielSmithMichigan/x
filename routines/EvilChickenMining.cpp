#ifndef evilchickenmining_cpp
#define evilchickenmining_cpp
	#include "EvilChickenMining.h"

	EvilChickenMining::EvilChickenMining() {
		inventory.reset(new Inventory());
		rock.reset(new Rock());
	}

	EvilChickenMining::~EvilChickenMining() {
	}

	void EvilChickenMining::run() {
  		clock_t begin = clock();
  		double seconds, hours;
		double totalExp = 0;
		double expPerRock = 70;
		double remainingXp = 1086574;
		map<string, bool> flags;
		string str = "DUNGEON_ROCKS";
		flags[str] = true;
	    while (true) {
	        inventory->initialize();

	        if (!inventory->full) {
	        	cout << "INVENTORY NOT FULL" << endl;
	        	if(rock->use("IRON", flags)) {
	        		inventory->waitForItem();
	        		totalExp += expPerRock;
	        		remainingXp -= expPerRock;
  					clock_t end = clock();
  					seconds = double(end - begin) / (CLOCKS_PER_SEC);
  					hours = seconds / (60 * 60);
  					cout << "Elapsed Seconds: " << seconds << endl;
  					cout << "Total exp: " << totalExp << endl;
  					cout << "Exp/Hour: " << (totalExp / hours) << endl;
  					cout << "Hours Remaining: " << remainingXp / (totalExp / hours) << endl;
	        	} else {
	        		cout << "NO ROCKS" << endl;
	        		nsleep(1000);
	        	}
	        } else {
	        	cout << "INVENTORY FULL" << endl;
	        	inventory->dropAllItems();
	        }
	    }
	}

#endif