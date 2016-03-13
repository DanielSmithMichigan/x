#ifndef Smithing_h
#define Smithing_h
	#include "../objects/OreSmelter.h"
	#include "../objects/ArmorDeposit.h"
	#include "../objects/Anvil.h"
	#include "../ImageObject.h"
	#include "../Inventory.h"
	#include "../MapButton.h"
	#include "../Scene.h"
	#include "../Dialog.h"

	using namespace std;

	class Smithing {
		private:
			unique_ptr<MapButton> mapButton;
			unique_ptr<Scene> scene;
			unique_ptr<Dialog> dialog;
		protected:
		public:
			Smithing();
			virtual ~Smithing();
			void run();
	};
#endif