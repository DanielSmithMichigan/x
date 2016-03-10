#ifndef Fishing_h
#define Fishing_h

	#include "../objects/FishingSpot.h"
	#include "../Inventory.h"
	#include "../ImageObject.h"
	#include "../Template.h"
	#include "../Scene.h"

	using namespace std;

	class Fishing {
		private:
		protected:
		public:
			Fishing();
			virtual ~Fishing();
			void run();
	};
#endif