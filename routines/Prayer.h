#ifndef Prayer_h
#define Prayer_h

	#include "../objects/Chest.h"
	#include "../Inventory.h"
	#include "../ImageObject.h"
	#include "../Template.h"
	#include "../Scene.h"
	#include "../BankScreen.h"

	using namespace std;

	class Prayer {
		private:
		protected:
		public:
			Prayer();
			virtual ~Prayer();
			void run();
	};
#endif