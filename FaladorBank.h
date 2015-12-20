#ifndef FaladorBank_h
#define FaladorBank_h
	#include "OcrObject.h"
	#include "ErodeFilter.h"
	#include "RangeFilter.h"
	#include "Dialog.h"

	class FaladorBank {
		private:
			unique_ptr<Scene> scene;
			unique_ptr<RangeFilter> noteRange;
			unique_ptr<ErodeFilter> noteErode;
			unique_ptr<RangeFilter> bankFloorRange;
			unique_ptr<ErodeFilter> bankFloorErode;
			unique_ptr<ErodeFilter> bankFloorDilate;
			unique_ptr<RangeFilter> matRange;
			unique_ptr<ErodeFilter> matErode;
			unique_ptr<ErodeFilter> matDilate;
			unique_ptr<Dialog> dialog;
			int minGuessDistance;
		public:
			FaladorBank();
			~FaladorBank();
			bool use();
	};
#endif