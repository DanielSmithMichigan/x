#ifndef Minesite_h
#define Minesite_h
	#include "Inventory.h"

	class Minesite {
		private:
        	unique_ptr<Dialog> dialog;
        	unique_ptr<Inventory> inventory;
        	vector<unique_ptr<ImageObject>> imageObjects;
			void waitForOre(int startingAmount, int retries = 20);
		public:
			void Minesite::mine();
			Minesite();
			~Minesite();
	};
#endif