#ifndef AmuletStringing_h
#define AmuletStringing_h
	#include "../objects/Chest.h"
	#include "../BankScreen.h"
	#include "../Inventory.h"
	#include "../objects/ActionButton.h"

	using namespace std;

	class AmuletStringing {
		private:
			unique_ptr<Chest> chest;
			unique_ptr<ActionButton> actionButton;
			unique_ptr<BankScreen> bankScreen;
			unique_ptr<Inventory> inventory;
		protected:
		public:
			AmuletStringing();
			virtual ~AmuletStringing();
			void run();
	};
#endif