#ifndef BoxTrap_h
#define BoxTrap_h
	#include "../OcrObject.h"
	#include "../ErodeFilter.h"
	#include "../RangeFilter.h"
	#include "../WindowFilter.h"
	#include "../Dialog.h"

	class BoxTrap {
		private:
			unique_ptr<Scene> scene;
			unique_ptr<WindowFilter> windowFilter;
			unique_ptr<RangeFilter> boxRange;
			unique_ptr<RangeFilter> fallenBoxRange;
			unique_ptr<ErodeFilter> boxErode;
			unique_ptr<RangeFilter> rockRange;
			unique_ptr<ErodeFilter> rockErode;
			unique_ptr<ErodeFilter> rockDilate;
			unique_ptr<RangeFilter> stickRange;
			unique_ptr<RangeFilter> fallenStickRange;
			unique_ptr<ErodeFilter> stickDilate;
			unique_ptr<Dialog> dialog;
			float maxArea;
		public:
			BoxTrap();
			~BoxTrap();
			bool use();
	};
#endif