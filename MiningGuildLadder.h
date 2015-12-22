#ifndef MiningGuildLadder_h
#define MiningGuildLadder_h
	#include "OcrObject.h"
	#include "ErodeFilter.h"
	#include "RangeFilter.h"
	#include "Dialog.h"

	class MiningGuildLadder {
		private:
			unique_ptr<Scene> scene;
			unique_ptr<RangeFilter> ladderRange;
			unique_ptr<ErodeFilter> ladderErode;
			unique_ptr<Dialog> dialog;
			int minGuessDistance;
		public:
			MiningGuildLadder();
			~MiningGuildLadder();
			bool use();
	};
#endif