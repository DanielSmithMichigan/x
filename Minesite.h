#ifndef Minesite_h
#define Minesite_h
	#include "Inventory.h"
	#include "Map.h"

	class Minesite {
		private:
			unique_ptr<Map> interfaceMap;
        	unique_ptr<Dialog> dialog;
        	unique_ptr<Inventory> inventory;
        	vector<unique_ptr<ImageObject>> rocks;
			unique_ptr<Scene> scene;
			void waitForOre(int startingAmount, int retries = 20);
		public:
			void mine(string miningLocation);
			Minesite();
			~Minesite();
	};
#endif