#ifndef Minesite_h
#define Minesite_h
	#include "Inventory.h"
	#include "Map.h"
	#include "Rock.h"

	class Minesite {
		private:
			unique_ptr<Map> interfaceMap;
        	unique_ptr<Inventory> inventory;
        	unique_ptr<Rock> rock;
			unique_ptr<Scene> scene;
			void waitForOre(int startingAmount, int retries = 20);
		public:
			void mine(string miningLocation, string oreType = "COAL_OR_MITHRIL", int oreAmount = 9999, int retries = 9999);
			Minesite();
			~Minesite();
	};
#endif