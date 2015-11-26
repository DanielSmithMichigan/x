#ifndef inventory_h
#define inventory_h
	#include "ImageObject.h"
	#include "Scene.h"
	#include "utilities.h"

	using namespace std;

	class Inventory {
		private:
			static Object *items[4][7];
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
	};
#endif