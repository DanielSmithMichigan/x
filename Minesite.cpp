#ifndef Minesite_cpp
#define Minesite_cpp
	#include "Minesite.h"

	Minesite::Minesite() {
        interfaceMap.reset(new Map());
        scene.reset(new Scene());
        inventory.reset(new Inventory());
        rock.reset(new Rock());
	}

	Minesite::~Minesite() {
	}

    void Minesite::initialize() {
        interfaceMap->initialize();
    }

    void Minesite::mine(string miningLocation, string oreType, int oreAmount, int retries) {
        while(!inventory->full 
              && inventory->numItems < oreAmount
              && retries-- > 0) {
            if (chance(1000)) {
                nsleep(1000 * 60);
            }
            if (chance(100)) {
                nsleep(1000 * 30);
            }
            inventory->initialize();
            if (rock->use(oreType, interfaceMap->getFlags(miningLocation))) {
                inventory->waitForItem();
                interfaceMap->goTo(miningLocation, 45);
            }

            nsleep(250);
        }
    }
#endif