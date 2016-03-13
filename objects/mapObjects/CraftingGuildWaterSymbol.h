#ifndef CraftingGuildWaterSymbol_h
#define CraftingGuildWaterSymbol_h
	#include "../../ImageObject.h"
	#include "../../Template.h"

	class CraftingGuildWaterSymbol : public Object {
		private:
		public:
			CraftingGuildWaterSymbol();
			~CraftingGuildWaterSymbol();
			bool initialize();
			void goToMinesite();
			void goToCraftingGuildCenter();
	};
#endif