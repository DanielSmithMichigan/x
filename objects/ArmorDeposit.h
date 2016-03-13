#ifndef ArmorDeposit_h
#define ArmorDeposit_h
	#include "../OcrObject.h"
	#include "../ErodeFilter.h"
	#include "../RangeFilter.h"
	#include "../WindowFilter.h"
	#include "../Select.h"

	class ArmorDeposit {
		private:
			unique_ptr<Scene> scene;
			unique_ptr<Dialog> dialog;
			unique_ptr<WindowFilter> windowFilter;
			unique_ptr<RangeFilter> blacknessRange;
			unique_ptr<ErodeFilter> blacknessErode;
			unique_ptr<RangeFilter> handRailRange;
			unique_ptr<ErodeFilter> handRailErode;
			unique_ptr<ErodeFilter> handRailDilate;
			unique_ptr<Select> select;
			vector<string> goodDialog;
			vector<string> badDialog;
		public:
			ArmorDeposit();
			~ArmorDeposit();
			bool use();
	};
#endif