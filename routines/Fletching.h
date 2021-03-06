#ifndef Fletching_h
#define Fletching_h

	#include "../objects/Chest.h"
	#include "../Inventory.h"
	#include "../ImageObject.h"
	#include "../Template.h"
	#include "../Scene.h"
	#include "../BankScreen.h"
	#include "../objects/ActionButton.h"

	using namespace std;

	class Fletching {
		private:
			unique_ptr<ActionButton> actionButton;
		protected:
		public:
			Fletching();
			virtual ~Fletching();
			void run();
	};
#endif