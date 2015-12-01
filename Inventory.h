#ifndef inventory_h
#define inventory_h
	#include "ImageObject.h"
	#include "Scene.h"
	#include "ThresholdTemplate.h"
	#include "utilities.h"
	#define INVENTORY_ROWS 7
	#define INVENTORY_COLS 4

	using namespace std;

	class Inventory {
		private:
			static Object *items[INVENTORY_COLS][INVENTORY_ROWS];
			static bool slotEmpty[INVENTORY_COLS][INVENTORY_ROWS];
			static int width;
			static int marginTop;
			static int marginLeft;
			static int cellWidth;
			static int cellHeight;
			static int cellMarginX;
			static int cellMarginY;
		public:
			Inventory();
			static void initialize();
			static void dropItem(int x, int y);
			static void dropAllItems();
			static cv::Mat imageFromSlot(int x, int y);
			static void markEmptyCells();
	};
#endif