#ifndef MiningGuildLadder_h
#define MiningGuildLadder_h
	#include "OcrObject.h"
	#include "ErodeFilter.h"
	#include "RangeFilter.h"
	#include "WindowFilter.h"
	#include "Select.h"

	class MiningGuildLadder {
		private:
			unique_ptr<Scene> scene;
			unique_ptr<WindowFilter> windowFilter;
			unique_ptr<RangeFilter> ladderRange;
			unique_ptr<ErodeFilter> ladderErode;
			unique_ptr<Select> select;
			vector<string> goodDialog;
			vector<string> badDialog;
		public:
			MiningGuildLadder();
			virtual ~MiningGuildLadder();
			bool use();
	};
#endif