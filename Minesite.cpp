#ifndef Minesite_cpp
#define Minesite_cpp
	#include "Minesite.h"

	Minesite::Minesite() {
        interfaceMap.reset(new Map());
        interfaceMap->initialize();
        scene.reset(new Scene());
        inventory.reset(new Inventory());
        rock.reset(new Rock());
	}

	Minesite::~Minesite() {
	}

    void Minesite::mine(string miningLocation) {
        while(!inventory->full) {
            if (chance(1000)) {
                nsleep(1000 * 60);
            }
            if (chance(100)) {
                nsleep(1000 * 30);
            }
            inventory->initialize();
            if (rock->use()) {
                scene->redraw();
                inventory->markEmptyCells();
                waitForOre(inventory->numItems);
                interfaceMap->goTo(miningLocation, 45);
            }

            nsleep(100);
        }
    }

    void Minesite::waitForOre(int startingAmount, int retries) {
        cout << "Retries: " << retries << endl;
        if (retries <= 0) {
            return;
        }
        if (inventory->numItems > startingAmount) {
            return;
        }
        nsleep(1000);
        scene->redraw();
        inventory->markEmptyCells();
        waitForOre(startingAmount, --retries);
    }
#endif