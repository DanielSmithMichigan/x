#ifndef CraftingFurnace_h
#define CraftingFurnace_h
	#include "../ErodeFilter.h"
	#include "../RangeFilter.h"
	#include "../WindowFilter.h"
	#include "../Select.h"
	#include "../Inventory.h"
	#include "../ImageObject.h"

	class CraftingFurnace {
		private:
			unique_ptr<Scene> scene;
			unique_ptr<Dialog> dialog;
			unique_ptr<WindowFilter> windowFilter;
			unique_ptr<RangeFilter> ringRange;
			unique_ptr<ErodeFilter> ringErode;
			unique_ptr<RangeFilter> fireRange;
			unique_ptr<ErodeFilter> fireErode;
			unique_ptr<ErodeFilter> fireDilate;
			unique_ptr<Select> select;
			unique_ptr<ImageObject> fireButton;
			vector<string> goodDialog;
			vector<string> badDialog;
		public:
			CraftingFurnace();
			~CraftingFurnace();
			bool use();
	};
#endif