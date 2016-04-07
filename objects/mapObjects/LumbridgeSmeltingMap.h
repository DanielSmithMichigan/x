#ifndef LumbridgeSmeltingMap_h
#define LumbridgeSmeltingMap_h
	#include "../../ImageObject.h"
	#include "../../Template.h"
	#include "../../Map.h"

	class LumbridgeSmeltingMap : public Object {
		private:
			unique_ptr<Map> map;
		public:
			LumbridgeSmeltingMap();
			~LumbridgeSmeltingMap();
			bool initialize();
			void goToBank();
			void goToFurnace();
	};
#endif