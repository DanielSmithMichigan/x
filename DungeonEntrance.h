#ifndef DungeonEntrance_h
#define DungeonEntrance_h
	#include "OcrObject.h"
	#include "ErodeFilter.h"
	#include "RangeFilter.h"
	#include "WindowFilter.h"
	#include "Select.h"

	class DungeonEntrance {
		private:
			unique_ptr<Scene> scene;
			unique_ptr<WindowFilter> windowFilter;
			unique_ptr<RangeFilter> symbolRange;
			unique_ptr<ErodeFilter> symbolErode;
			unique_ptr<RangeFilter> entranceOneRange;
			unique_ptr<ErodeFilter> entranceOneErode;
			unique_ptr<ErodeFilter> entranceOneDilate;
			unique_ptr<RangeFilter> entranceTwoRange;
			unique_ptr<ErodeFilter> entranceTwoErode;
			unique_ptr<ErodeFilter> entranceTwoDilate;
			unique_ptr<Select> select;
			vector<string> goodDialog;
			vector<string> badDialog;
		public:
			DungeonEntrance();
			~DungeonEntrance();
			bool use();
	};
#endif