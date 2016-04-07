#ifndef GoldSmithing_h
#define GoldSmithing_h
	#include "../objects/SmeltingFurnace.h"
	#include "../objects/mapObjects/LumbridgeSmeltingMap.h"
	#include "../objects/Chest.h"
	#include "../BankScreen.h"
	#include "../Inventory.h"

	using namespace std;

	class GoldSmithing {
		private:
			unique_ptr<SmeltingFurnace> smeltingFurnace;
			unique_ptr<Chest> chest;
			unique_ptr<BankScreen> bankScreen;
			unique_ptr<Inventory> inventory;
			unique_ptr<LumbridgeSmeltingMap> lumbridgeSmeltingMap;
		protected:
		public:
			GoldSmithing();
			virtual ~GoldSmithing();
			void run();
	};
#endif