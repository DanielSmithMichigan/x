#ifndef SmeltingFurnace_h
#define SmeltingFurnace_h
	#include "../ErodeFilter.h"
	#include "../RangeFilter.h"
	#include "../ShiftFilter.h"
	#include "../WindowFilter.h"
	#include "../Select.h"
	#include "../Inventory.h"
	#include "../ImageObject.h"
	#include "ActionButton.h"

	class SmeltingFurnace {
		private:
			unique_ptr<ActionButton> actionButton;
			unique_ptr<Scene> scene;
			unique_ptr<Dialog> dialog;
			unique_ptr<WindowFilter> windowFilter;
			unique_ptr<RangeFilter> redRange;
			unique_ptr<ErodeFilter> redErode;
			unique_ptr<ErodeFilter> redRoofDilate;
			unique_ptr<ShiftFilter> redRoofShiftFilter;
			unique_ptr<RangeFilter> gateRange;
			unique_ptr<ErodeFilter> gateErode;
			unique_ptr<ErodeFilter> gateDilate;
			unique_ptr<RangeFilter> hammerRange;
			unique_ptr<ErodeFilter> hammerErode;
			unique_ptr<ErodeFilter> hammerDilate;
			unique_ptr<RangeFilter> bricksRange;
			unique_ptr<ErodeFilter> bricksErode;
			unique_ptr<ErodeFilter> bricksDilate;
			unique_ptr<Select> select;
			vector<string> goodDialog;
			vector<string> badDialog;
		public:
			SmeltingFurnace();
			~SmeltingFurnace();
			bool use();
	};
#endif