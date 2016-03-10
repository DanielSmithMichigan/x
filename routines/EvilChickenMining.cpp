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
		double currentXp = 3222101;
		double goalXp = 3258594;
		double remainingXp = goalXp - currentXp;
		double expPerHour = 29000;
		double hoursRemaining = 0;
		map<string, bool> flags;
		string str = "DUNGEON_ROCKS";
		flags[str] = true;
	    while (true) {
	        inventory->initialize();

	        if (!inventory->full) {
	        	if(rock->use("IRON", flags)) {
	        		inventory->waitForItem();
	        		totalExp += expPerRock;
  					clock_t end = clock();
  					seconds = double(end - begin) / (CLOCKS_PER_SEC);
  					hours = seconds / (60 * 60 * .18);
  					hoursRemaining = (remainingXp - totalExp) / expPerHour;
  					system("clear");
  					cout << "Elapsed hours: " << hours << endl;
  					cout << "Total exp: " << totalExp << endl;
  					cout << "Exp/Hour: " << expPerHour << endl;
  					cout << "Hours Remaining: " << hoursRemaining << endl;
  					cout << "PCT: " << ((int)((totalExp / remainingXp) * 100)) << endl;
	        	} else {
	        		nsleep(1000);
	        	}
	        } else {
	        	inventory->dropAllItems();
	        }
	    }
	}

#endif