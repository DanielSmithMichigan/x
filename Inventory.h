#ifndef inventory_h
#define inventory_h
	#include "Dialog.h"
	#include "Scene.h"
	#include "Template.h"
	#include "utilities.h"
	#define INVENTORY_ROWS 7
	#define INVENTORY_COLS 4

	using namespace std;

	class Inventory {
		private:
			static unique_ptr<Object> items[INVENTORY_COLS][INVENTORY_ROWS];
			static bool slotEmpty[INVENTORY_COLS][INVENTORY_ROWS];
			static int width;
			static int marginTop;
			static int marginLeft;
			static int cellWidth;
			static int cellHeight;
			static int cellMarginX;
			static int cellMarginY;
			static unique_ptr<Scene> scene;
		public:
			Inventory();
			~Inventory();
			static void initialize();
			static void dropItem(int x, int y);
			static void dropAllItems();
			static void bankAllItems();
			static cv::Mat imageFromSlot(int x, int y);
			static void markEmptyCells();
			static int numItems;
			static bool full;
	};
#endif