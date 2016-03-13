#ifndef SaveInventory_h
#define SaveInventory_h
	#include "../Inventory.h"

	using namespace std;

	class SaveInventory {
		private:
		    unique_ptr<Inventory> inventory;
		protected:
		public:
			SaveInventory();
			virtual ~SaveInventory();
			void run();
	};
#endif