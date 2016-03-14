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
			virtual ~Inventory();
			static void initialize();
			static void dropItem(int x, int y);
			static void dropAllItems();
			static void bankAllItems();
			static void saveAllItems();
			static void dropEverythingBut(vector<cv::Mat> imgs);
			static void dropEverythingBut(cv::Mat img);
			static int countItem(cv::Mat item);
			static cv::Point firstMatch(cv::Mat img);
			static cv::Point firstNonMatch(cv::Mat img);
			static cv::Point firstNonEmpty();
			static cv::Mat imageFromSlot(int x, int y);
			static void markEmptyCells();
			static void clickItem(int x, int y, int click);
			static void waitForItem(int startingAmount = -1, int retries = 20);
			static bool has(cv::Mat item);
			static void waitUntilGone(cv::Mat item, int waitTime = 3000);
			static int numItems;
			static bool full;
	};
#endif