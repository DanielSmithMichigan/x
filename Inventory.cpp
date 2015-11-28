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
	Object* Inventory::items[INVENTORY_COLS][INVENTORY_ROWS] = {};
	bool Inventory::slotEmpty[INVENTORY_COLS][INVENTORY_ROWS] = {};

	Inventory::Inventory() {
	}

	void Inventory::initialize() {
		ImageObject *topOfInventory = new ImageObject("../images/top_of_inventory.png");
		topOfInventory->initialize();
		for (int i = 0; i < INVENTORY_COLS; i++) {
			int x = topOfInventory->topLeft.x + marginLeft + (i * cellWidth) + (i * cellMarginX * 2);
			for (int j = 0; j < INVENTORY_ROWS; j++) {
				int y = topOfInventory->topLeft.y + marginTop + (j * cellHeight) + (j * cellMarginY * 2);
				items[i][j] = new Object();
				items[i][j]->topLeft = cv::Point(x, y);
				items[i][j]->width = cellWidth;
				items[i][j]->height = cellHeight;
				items[i][j]->initialize();
			}
		}
		markEmptyCells();
	}

	void Inventory::dropItem(int x, int y) {
		items[x][y]->clickOn(RIGHT_CLICK);
		Scene *scene = new Scene();
		scene->redraw();
		ImageObject *dropButton = new ImageObject("../images/drop_button.png");
		dropButton->initialize();
		dropButton->draw();
		dropButton->clickOn();
	}

	void Inventory::dropAllItems() {
		for (int i = 0; i < INVENTORY_COLS; i++) {
			for (int j = 0; j < INVENTORY_ROWS; j++) {
				if (slotEmpty[i][j]) {
					continue;
				}
				dropItem(i, j);
				nsleep(500);
			}
		}
	}

	void Inventory::markEmptyCells() {
		cv::Mat emptySlotImage = cv::imread("../images/empty_slot.png");
		for (int i = 0; i < INVENTORY_COLS; i++) {
			for (int j = 0; j < INVENTORY_ROWS; j++) {
				slotEmpty[i][j] = imagesEqual(imageFromSlot(i, j), emptySlotImage);
			}
		}
	}

	cv::Mat Inventory::imageFromSlot(int x, int y) {
		return ImageFromDisplay(items[x][y]->width, items[x][y]->height, items[x][y]->topLeft.x, items[x][y]->topLeft.y);
	}
#endif