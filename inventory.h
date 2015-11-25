#include "utilities.h"
#include "interface.h"
#include "ClickableImageObject.h"

using namespace std;

class Inventory {
	public:
		Inventory();
		static void initialize(cv::Mat &sceneImage);
	private:
		static ClickableImageObject *items[26];
		static int inventoryWidth;
		static int inventoryMarginTop;
		static int inventoryMarginLeft;
};