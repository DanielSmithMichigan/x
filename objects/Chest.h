#ifndef Chest_h
#define Chest_h
	#include "../OcrObject.h"
	#include "../ErodeFilter.h"
	#include "../RangeFilter.h"
	#include "../WindowFilter.h"
	#include "../Dialog.h"
	#include "../Select.h"
	#include "../ImageObject.h"
	#include "../BankScreen.h"
	class Chest {
		private:
			string location;
			unique_ptr<Scene> scene;
			unique_ptr<BankScreen> bankScreen;
			unique_ptr<WindowFilter> windowFilter;
			unique_ptr<RangeFilter> blacknessRange;
			unique_ptr<ErodeFilter> blacknessErode;
			unique_ptr<ErodeFilter> blacknessDilate;
			unique_ptr<RangeFilter> rockRange;
			unique_ptr<ErodeFilter> rockErode;
			unique_ptr<ErodeFilter> rockDilate;
			unique_ptr<RangeFilter> bookRange;
			unique_ptr<ErodeFilter> bookErode;
			unique_ptr<ErodeFilter> bookDilate;
			unique_ptr<RangeFilter> chestRange;
			unique_ptr<ErodeFilter> chestErode;
			unique_ptr<ErodeFilter> chestDilate;
			unique_ptr<RangeFilter> lockRange;
			unique_ptr<Dialog> dialog;
			unique_ptr<Select> select;
			vector<string> goodDialog;
			vector<string> badDialog;
			float maxArea;
		public:
			Chest(string location = "PORT_SARIM");
			~Chest();
			bool use();
			void storeAll();
			void loadPresetOne();
			bool open();
	};
#endif