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
		dialogBoxes;
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
			dialogBoxes.push_back(currDialogBox);
		}
	}

	void Dialog::select(string matchString)
	{
		cout << "Attemping to find " << matchString << endl;
		for(std::vector<OcrObject*>::iterator iter = dialogBoxes.begin(); iter != dialogBoxes.end(); ++iter) {
			if ((*iter)->match(matchString)) {
				cout << "Found match" << endl;
				(*iter)->clickOn();
				return;
			}
		}
	}
#endif