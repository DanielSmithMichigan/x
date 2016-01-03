#ifndef Rock_h
#define Rock_h
	#include "OcrObject.h"
	#include "ErodeFilter.h"
	#include "RangeFilter.h"
	#include "CornerFilter.h"
	#include "Dialog.h"

	class Rock {
		private:
			unique_ptr<Scene> scene;
			unique_ptr<RangeFilter> rockBaseRange;
			unique_ptr<ErodeFilter> rockBaseErode;
			unique_ptr<ErodeFilter> rockBaseDilate;
			unique_ptr<ErodeFilter> oreErode;
			unique_ptr<ErodeFilter> oreDilate;
			unique_ptr<RangeFilter> coalRange;
			unique_ptr<RangeFilter> mithrilRange;
			unique_ptr<RangeFilter> adamRange;
			unique_ptr<Dialog> dialog;
			int minGuessDistance;
		public:
			Rock();
			~Rock();
			bool use();
			string oreType;
	};
#endif