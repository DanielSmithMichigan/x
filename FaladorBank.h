#ifndef FaladorBank_h
#define FaladorBank_h
	#include "OcrObject.h"
	#include "ErodeFilter.h"
	#include "RangeFilter.h"
	#include "WindowFilter.h"
	#include "ImageObject.h"
	#include "Select.h"

	class FaladorBank {
		private:
			unique_ptr<Scene> scene;
			unique_ptr<WindowFilter> windowFilter;
			unique_ptr<RangeFilter> noteRange;
			unique_ptr<ErodeFilter> noteErode;
			unique_ptr<RangeFilter> bankFloorRange;
			unique_ptr<ErodeFilter> bankFloorErode;
			unique_ptr<ErodeFilter> bankFloorDilate;
			unique_ptr<RangeFilter> matRange;
			unique_ptr<ErodeFilter> matErode;
			unique_ptr<ErodeFilter> matDilate;
			unique_ptr<RangeFilter> matTwoRange;
			unique_ptr<Select> select;
			vector<string> goodDialog;
			vector<string> badDialog;
		public:
			FaladorBank();
			virtual ~FaladorBank();
			bool use();
			bool open();
			bool close();
	};
#endif