#ifndef Minesite_h
#define Minesite_h
	#include "Inventory.h"

	class Minesite {
		private:
        	unique_ptr<Dialog> dialog;
        	unique_ptr<Inventory> inventory;
        	vector<unique_ptr<ImageObject>> rocks;
			unique_ptr<Scene> scene;
			void waitForOre(int startingAmount, int retries = 20);
		public:
			void mine();
			Minesite();
			~Minesite();
	};
#endif