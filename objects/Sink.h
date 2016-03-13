#ifndef Sink_h
#define Sink_h
	#include "../ErodeFilter.h"
	#include "../RangeFilter.h"
	#include "../WindowFilter.h"
	#include "../Select.h"
	#include "../Inventory.h"
	#include "../ImageObject.h"

	class Sink {
		private:
			unique_ptr<Scene> scene;
			unique_ptr<Dialog> dialog;
			unique_ptr<WindowFilter> windowFilter;
			unique_ptr<RangeFilter> waterRange;
			unique_ptr<ErodeFilter> waterErode;
			unique_ptr<RangeFilter> sinkRange;
			unique_ptr<ErodeFilter> sinkErode;
			unique_ptr<ErodeFilter> sinkDilate;
			unique_ptr<Select> select;
			vector<string> goodDialog;
			vector<string> badDialog;
			unique_ptr<ImageObject> softenButton;
		public:
			Sink();
			~Sink();
			static void beforeSelect();
			bool use();
	};
#endif