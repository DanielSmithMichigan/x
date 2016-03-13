#ifndef PottersWheel_h
#define PottersWheel_h
	#include "../ErodeFilter.h"
	#include "../RangeFilter.h"
	#include "../WindowFilter.h"
	#include "../Select.h"
	#include "../Inventory.h"
	#include "../ImageObject.h"

	class PottersWheel {
		private:
			unique_ptr<Scene> scene;
			unique_ptr<Dialog> dialog;
			unique_ptr<WindowFilter> windowFilter;
			unique_ptr<RangeFilter> wheelRange;
			unique_ptr<ErodeFilter> wheelErode;
			unique_ptr<RangeFilter> boxRange;
			unique_ptr<ErodeFilter> boxErode;
			unique_ptr<ErodeFilter> boxDilate;
			unique_ptr<Select> select;
			unique_ptr<ImageObject> mouldButton;
			vector<string> goodDialog;
			vector<string> badDialog;
		public:
			PottersWheel();
			~PottersWheel();
			bool use();
	};
#endif