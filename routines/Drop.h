#ifndef drop_h
#define drop_h

	#include "../Inventory.h"

	using namespace std;

	class Drop {
		private:
			unique_ptr<Inventory> inventory;
		protected:
		public:
			Drop();
			virtual ~Drop();
			void run();
	};
#endif