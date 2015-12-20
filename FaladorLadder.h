#ifndef FaladorLadder_h
#define FaladorLadder_h
	#include "OcrObject.h"
	#include "ErodeFilter.h"
	#include "RangeFilter.h"
	#include "Dialog.h"

	class FaladorLadder {
		private:
			unique_ptr<Scene> scene;
			unique_ptr<RangeFilter> ladderRange;
			unique_ptr<ErodeFilter> ladderErode;
			unique_ptr<RangeFilter> ladderStructureRange;
			unique_ptr<ErodeFilter> ladderStructureErode;
			unique_ptr<ErodeFilter> ladderStructureDilate;
			unique_ptr<RangeFilter> blacknessRange;
			unique_ptr<ErodeFilter> blacknessErode;
			unique_ptr<ErodeFilter> blacknessDilate;
			unique_ptr<RangeFilter> graynessRange;
			unique_ptr<ErodeFilter> graynessErode;
			unique_ptr<ErodeFilter> graynessDilate;
			unique_ptr<Dialog> dialog;
			int minGuessDistance;
		public:
			FaladorLadder();
			~FaladorLadder();
			bool use();
	};
#endif