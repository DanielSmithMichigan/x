#ifndef inventory_cpp
#define inventory_cpp
	#include "Inventory.h"

	int Inventory::width = 210;
	int Inventory::marginTop = 20;
	int Inventory::marginLeft = 14;
	int Inventory::cellWidth = 29;
	int Inventory::cellHeight = 26;
	int Inventory::cellMarginX = 10;
	int Inventory::cellMarginY = 5;
	int Inventory::numItems = 0;
	unique_ptr<Object> Inventory::items[INVENTORY_COLS][INVENTORY_ROWS] = {};
	bool Inventory::slotEmpty[INVENTORY_COLS][INVENTORY_ROWS] = {};
	bool Inventory::full = false;
	bool Inventory::empty = false;
	unique_ptr<Scene> Inventory::scene(new Scene());

	Inventory::Inventory() {
	}

	Inventory::~Inventory() {
		
	}

	void Inventory::initialize() {
		scene->redraw();
		unique_ptr<ImageObject> topOfInventory(new ImageObject("../images/TopOfInventory.png"));
		topOfInventory->initialize();
		for (int i = 0; i < INVENTORY_COLS; i++) {
			int x = topOfInventory->topLeft.x + marginLeft + (i * cellWidth) + (i * cellMarginX * 2);
			for (int j = 0; j < INVENTORY_ROWS; j++) {
				int y = topOfInventory->topLeft.y + marginTop + (j * cellHeight) + (j * cellMarginY * 2);
				items[i][j] = unique_ptr<Object>(new Object());
				items[i][j]->topLeft = cv::Point(x, y);
				items[i][j]->width = cellWidth;
				items[i][j]->height = cellHeight;
				items[i][j]->initialize();
			}
		}
		markEmptyCells();
	}

	void Inventory::saveAllItems() {
		for (int i = 0; i < INVENTORY_COLS; i++) {
			for (int j = 0; j < INVENTORY_ROWS; j++) {
				items[i][j]->saveImage(to_string(i) + "_" + to_string(j) + ".png");
			}
		}
	}

	cv::Point Inventory::firstMatch(cv::Mat img) {
		for (int i = 0; i < INVENTORY_COLS; i++) {
			for (int j = 0; j < INVENTORY_ROWS; j++) {
				if (imagesEqual(imageFromSlot(i, j), img)) {
					return cv::Point(i, j);
				}
			}
		}
		return cv::Point(-1, -1);
	}

	cv::Point Inventory::firstNonMatch(cv::Mat img) {
		for (int i = 0; i < INVENTORY_COLS; i++) {
			for (int j = 0; j < INVENTORY_ROWS; j++) {
				if (!slotEmpty[i][j]
					&& !imagesEqual(imageFromSlot(i, j), img)) {
					return cv::Point(i, j);
				}
			}
		}
		return cv::Point(-1, -1);
	}

	void Inventory::dropEverythingBut(cv::Mat img) {
		vector<cv::Mat> imgs;
		imgs.push_back(img);
		dropEverythingBut(imgs);
		return;
	}

	void Inventory::dropEverythingBut(vector<cv::Mat> imgs) {
		for (int i = 0; i < INVENTORY_COLS; i++) {
			for (int j = 0; j < INVENTORY_ROWS; j++) {
				if (!slotEmpty[i][j]) {
					bool match = false;
					for(vector<cv::Mat>::iterator img = imgs.begin(); img != imgs.end(); ++img) {
						if (imagesEqual(imageFromSlot(i, j), *img)) {
							match = true;
							break;
						}
					}
					if (match) {
						continue;
					}
					dropItem(i, j);
				}
			}
		}
		return;
	}

	cv::Point Inventory::firstNonEmpty() {
		for (int i = 0; i < INVENTORY_COLS; i++) {
			for (int j = 0; j < INVENTORY_ROWS; j++) {
				if (slotEmpty[i][j]) {
					continue;
				}
				return cv::Point(i, j);
			}
		}
		return cv::Point(-1, -1);
	}

	void Inventory::dropItem(int x, int y) {
		items[x][y]->clickOn(RIGHT_CLICK);
		unique_ptr<Dialog> dialog(new Dialog());
		if (dialog->initialize()) {
			if (true 
				// && !dialog->match("DropUncut")
				&& !dialog->match("DropBarbarianrod")
				&& !dialog->match("DropFishingbait")
				&& !dialog->match("DropLeapingsalmon")
				&& !dialog->match("DropWoodcutti")
				&& dialog->match("Drop")) {
				dialog->select("Drop");
				nsleep(400);
			} else {
				dialog->select("Cancel");
			}
		}
	}

	void Inventory::dropAllItems() {
		markEmptyCells();
		for (int i = 0; i < INVENTORY_COLS; i++) {
			for (int j = 0; j < INVENTORY_ROWS; j++) {
				if (slotEmpty[i][j]) {
					continue;
				}
				dropItem(i, j);
			}
		}
	}

	void Inventory::bankAllItems() {
		markEmptyCells();
		for (int i = 0; i < INVENTORY_COLS; i++) {
			for (int j = 0; j < INVENTORY_ROWS; j++) {
				if (slotEmpty[i][j]) {
					continue;
				}
				items[i][j]->clickOn(RIGHT_CLICK);
				unique_ptr<Dialog> dialog(new Dialog());
				if (dialog->initialize()) {
					if (dialog->match("OepositStro")
						|| dialog->match("OepositAllStro")) {
						dialog->select("Cancel");
						nsleep(100);
					} else if (dialog->match("Deposit-All")) {
						dialog->select("Deposit-All");
						nsleep(100);
						markEmptyCells();
					} else if (dialog->match("OepositAll")) {
						dialog->select("OepositAll");
						nsleep(100);
						markEmptyCells();
					} else if (dialog->match("Oeposit")) {
						dialog->select("Oeposit");
						nsleep(100);
						markEmptyCells();
					} else {
						dialog->select("Cancel");
					}
				}
				nsleep(200);
			}
		}
	}


	void Inventory::markEmptyCells() {
		numItems = 0;
		full = true;
		empty = true;
		cv::Mat emptySlotImage = cv::imread("../images/EmptySlot.png");
		for (int i = 0; i < INVENTORY_COLS; i++) {
			for (int j = 0; j < INVENTORY_ROWS; j++) {
				slotEmpty[i][j] = imagesEqual(imageFromSlot(i, j), emptySlotImage);
				if (slotEmpty[i][j]) {
					full = false;
				} else {
					empty = false;
					numItems++;
				}
			}
		}
	}

	void Inventory::clickItem(int x, int y, int click) {
		items[x][y]->clickOn(click);
	}

	cv::Mat Inventory::imageFromSlot(int x, int y) {
		return ImageFromDisplay(items[x][y]->width, items[x][y]->height, items[x][y]->topLeft.x, items[x][y]->topLeft.y);
	}

	void Inventory::waitUntilGone(cv::Mat item, int waitTime) {
		int numRetries = 0;
		while(has(item)) {
			numRetries++;
			cout << "Retry: " << numRetries << endl;
			nsleep(waitTime);
		}
	}

	vector<cv::Point> Inventory::getAllMatches(cv::Mat item) {
		vector<cv::Point> matches;
		scene->redraw();
		for (int j = 0; j < INVENTORY_ROWS; j++) {
			for (int i = 0; i < INVENTORY_COLS; i++) {
				if (imagesEqual(imageFromSlot(i, j), item)) {
					matches.push_back(cv::Point(i, j));
				}
			}
		}
		return matches;
	}

	bool Inventory::has(cv::Mat item) {
		scene->redraw();
		for (int i = 0; i < INVENTORY_COLS; i++) {
			for (int j = 0; j < INVENTORY_ROWS; j++) {
				if (imagesEqual(imageFromSlot(i, j), item)) {
					return true;
				}
			}
		}
		return false;
	}

	int Inventory::countItem(cv::Mat item) {
		scene->redraw();
		int count = 0;
		for (int i = 0; i < INVENTORY_COLS; i++) {
			for (int j = 0; j < INVENTORY_ROWS; j++) {
				if (imagesEqual(imageFromSlot(i, j), item)) {
					count ++;
				}
			}
		}

		cout << "Count: " << count << endl;
		return count;
	}


    void Inventory::waitForItem(int startingAmount, int retries) {
    	if (startingAmount == -1) {
            scene->redraw();
            markEmptyCells();
    		startingAmount = numItems;
    	}

        // cout << "Retries: " << retries << endl;
        if (retries <= 0) {
            return;
        }
        if (numItems > startingAmount) {
            return;
        }
        nsleep(1000);
        scene->redraw();
        markEmptyCells();
        waitForItem(startingAmount, --retries);
    }
#endif