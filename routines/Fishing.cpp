#ifndef Fishing_cpp
#define Fishing_cpp
	#include "Fishing.h"

	Fishing::Fishing() {

	}

	Fishing::~Fishing() {

	}

	void Fishing::run() {
		unique_ptr<FishingSpot> fishingSpot(new FishingSpot());
		int x = 0;
		while(!fishingSpot->use()) {
			cout << "Retry: " << ++x << endl;
			cout << flush;
		}
	}

#endif