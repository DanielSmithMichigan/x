#ifndef AmuletCharging_h
#define AmuletCharging_h
	#include "../objects/Chest.h"
	#include "../BankScreen.h"
	#include "../Inventory.h"
	#include "../ActionBar.h"

	using namespace std;

	class AmuletCharging {
		private:
			unique_ptr<Chest> chest;
			unique_ptr<ActionBar> actionBar;
			unique_ptr<BankScreen> bankScreen;
			unique_ptr<Inventory> inventory;
		protected:
		public:
			AmuletCharging();
			virtual ~AmuletCharging();
			void run(string spellName="ENCHANT_DIAMOND_JEWELRY");
	};
#endif