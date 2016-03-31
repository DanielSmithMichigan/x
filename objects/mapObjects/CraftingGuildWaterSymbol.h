#ifndef CraftingGuildWaterSymbol_h
#define CraftingGuildWaterSymbol_h
	#include "../../ImageObject.h"
	#include "../../Template.h"
	#include "../../Map.h"

	class CraftingGuildWaterSymbol : public Object {
		private:
			unique_ptr<Map> map;
		public:
			CraftingGuildWaterSymbol();
			~CraftingGuildWaterSymbol();
			bool initialize();
			void goToMinesite();
			void goToCraftingGuildCenter();
	};
#endif