#ifndef evilchickenmining_h
#define evilchickenmining_h
	#include "../Inventory.h"
	#include "../Rock.h"
	#include <ctime>

	using namespace std;

	class EvilChickenMining {
		private:
		    unique_ptr<Inventory> inventory;
		    unique_ptr<Rock> rock;
		protected:
		public:
			EvilChickenMining();
			virtual ~EvilChickenMining();
			void run();
	};
#endif