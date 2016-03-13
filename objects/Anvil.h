#ifndef Anvil_h
#define Anvil_h
	#include "../ErodeFilter.h"
	#include "../RangeFilter.h"
	#include "../WindowFilter.h"
	#include "../Select.h"

	class Anvil {
		private:
			unique_ptr<Scene> scene;
			unique_ptr<Dialog> dialog;
			unique_ptr<WindowFilter> windowFilter;
			unique_ptr<RangeFilter> anvilRange;
			unique_ptr<ErodeFilter> anvilErode;
			unique_ptr<RangeFilter> anvilPieceRange;
			unique_ptr<ErodeFilter> anvilPieceErode;
			unique_ptr<ErodeFilter> anvilPieceDilate;
			unique_ptr<Select> select;
			vector<string> goodDialog;
			vector<string> badDialog;
		public:
			Anvil();
			~Anvil();
			bool use();
	};
#endif