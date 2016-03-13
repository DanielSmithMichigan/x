#ifndef OreSmelter_h
#define OreSmelter_h
	#include "../OcrObject.h"
	#include "../ErodeFilter.h"
	#include "../RangeFilter.h"
	#include "../WindowFilter.h"
	#include "../Select.h"

	class OreSmelter {
		private:
			unique_ptr<Scene> scene;
			unique_ptr<Dialog> dialog;
			unique_ptr<WindowFilter> windowFilter;
			unique_ptr<RangeFilter> purpleBarRange;
			unique_ptr<ErodeFilter> purpleBarErode;
			unique_ptr<ErodeFilter> purpleBarDilate;
			unique_ptr<RangeFilter> blueBarRange;
			unique_ptr<ErodeFilter> blueBarErode;
			unique_ptr<ErodeFilter> blueBarDilate;
			unique_ptr<Select> select;
			vector<string> goodDialog;
			vector<string> badDialog;
		public:
			OreSmelter();
			~OreSmelter();
			bool use();
	};
#endif