#ifndef DropButton_cpp
#define DropButton_cpp
	#include "Dialog.h"

	Dialog::Dialog() {
		marginTop = 1;
		marginCell = 0;
		cellHeight = 16 - (marginCell * 2);
	}

	void Dialog::initialize()
	{
		ImageObject *topOfDialog = new ImageObject("../images/choose_option.png");
		topOfDialog->initialize();
		ImageObject *bottomOfDialog = new ImageObject("../images/bottom_corner.png");
		bottomOfDialog->initialize();
		int cellWidth = (bottomOfDialog->topLeft.x - marginCell) - (topOfDialog->topLeft.x + marginCell);
		vector<OcrObject*> dialogBoxes;
		OcrObject* currDialogBox;
		for (int y = topOfDialog->topLeft.y + topOfDialog->height + marginTop; 
			y <= bottomOfDialog->topLeft.y; 
			y += cellHeight + marginCell) {
			y += marginCell;
			currDialogBox = new OcrObject();
			currDialogBox->topLeft = cv::Point(topOfDialog->topLeft.x + marginCell, y);
			currDialogBox->width = cellWidth;
			currDialogBox->height = cellHeight;
			currDialogBox->initialize();
			currDialogBox->draw(CV_RGB(255, 0, 0), 1);
		}
	}
#endif