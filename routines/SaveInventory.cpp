#ifndef SaveInventory_cpp
#define SaveInventory_cpp
	#include "SaveInventory.h"

	SaveInventory::SaveInventory() {
		inventory.reset(new Inventory());
	}

	SaveInventory::~SaveInventory() {

	}

	void SaveInventory::run() {
        inventory->initialize();
        inventory->saveAllItems();
	}

#endif