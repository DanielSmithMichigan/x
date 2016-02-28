#ifndef drop_cpp
#define drop_cpp
	#include "Drop.h"

	Drop::Drop() {
		inventory.reset(new Inventory());
	}

	Drop::~Drop() {

	}

	void Drop::run() {
		inventory->initialize();
		inventory->dropAllItems();
	}

#endif