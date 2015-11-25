#include "inventory.h"

Inventory::Inventory() {
	Inventory::inventoryWidth = 210;
	Inventory::inventoryMarginTop = 25;
	Inventory::inventoryMarginLeft = 5;
}

void Inventory::initialize(cv::Mat &sceneImage) {
	ClickableImageObject *topOfInventory = new ClickableImageObject("../images/top_of_inventory.png", sceneImage, CV_RGB(255,0,0));
	topOfInventory->initialize();
	int leftCoordinate = topOfInventory->coordinates.x - (Inventory::inventoryWidth / 2);
	
}