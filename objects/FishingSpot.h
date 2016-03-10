#ifndef FishingSpot_h
#define FishingSpot_h
	#include "../ErodeFilter.h"
	#include "../RangeFilter.h"
	#include "../WindowFilter.h"
	#include "../Dialog.h"
	#include "../Select.h"
	#include "../ImageObject.h"

	class FishingSpot {
		private:
			unique_ptr<Scene> scene;
			unique_ptr<WindowFilter> windowFilter;
			unique_ptr<RangeFilter> bubblesRange;
			unique_ptr<RangeFilter> waveRange;
			unique_ptr<ErodeFilter> waveErode;
			unique_ptr<ErodeFilter> waveDilate;
			unique_ptr<RangeFilter> waterSpotRange;
			unique_ptr<ErodeFilter> waterSpotErode;
			unique_ptr<ErodeFilter> waterSpotDilate;
			unique_ptr<Dialog> dialog;
			unique_ptr<Select> select;
			vector<string> goodDialog;
			vector<string> badDialog;
			float maxArea;
		public:
			FishingSpot();
			~FishingSpot();
			bool use();
	};
#endif