#ifndef DropButton_cpp
#define DropButton_cpp
	#include "Dialog.h"

	Dialog::Dialog() {
		unique_ptr<Scene> scene(new Scene());
		marginTop = 1;
		marginCell = 0;
		cellHeight = 16 - (marginCell * 2);
	}

	void Dialog::initialize()
	{
		scene->redraw();
		unique_ptr<ImageObject> topOfDialog(new ImageObject());
		unique_ptr<ImageTemplate> chooseOption(new ImageTemplate("../images/ChooseOption.png"));
		chooseOption->retries = 4;
		chooseOption->logFailure = true;
		topOfDialog->addTemplate(move(chooseOption));
		cout << "Searching top of dialog" << endl;
		topOfDialog->initialize();
		unique_ptr<ImageObject> bottomOfDialog (new ImageObject());
		unique_ptr<ImageTemplate> bottomCorner (new ImageTemplate("../images/BottomCorner.png"));
		bottomCorner->retries = 4;
		bottomCorner->logFailure = true;
		bottomOfDialog->addTemplate(move(bottomCorner));
		cout << "Searching bottom of dialog" << endl;
		bottomOfDialog->initialize();
		int cellWidth = (bottomOfDialog->topLeft.x - marginCell) - (topOfDialog->topLeft.x + marginCell);
		dialogBoxes.clear();
		for (int y = topOfDialog->topLeft.y + topOfDialog->height + marginTop; 
			y <= bottomOfDialog->topLeft.y; 
			y += cellHeight + marginCell) {
			y += marginCell;
			unique_ptr<OcrObject> currDialogBox(new OcrObject());
			currDialogBox->topLeft = cv::Point(topOfDialog->topLeft.x + marginCell, y);
			currDialogBox->width = cellWidth;
			currDialogBox->height = cellHeight;
			currDialogBox->initialize();
			dialogBoxes.push_back(move(currDialogBox));
		}
	}

	bool Dialog::match(string matchString)
	{
		cout << "Attemping to find " << matchString << endl;
		for(vector<unique_ptr<OcrObject>>::iterator iter = dialogBoxes.begin(); iter != dialogBoxes.end(); ++iter) {
			if ((*iter)->match(matchString)) {
				cout << "Found match" << endl;
				return true;
			}
		}
		return false;
	}

	bool Dialog::select(string matchString)
	{
		cout << "Attemping to find " << matchString << endl;
		for(vector<unique_ptr<OcrObject>>::iterator iter = dialogBoxes.begin(); iter != dialogBoxes.end(); ++iter) {
			if ((*iter)->match(matchString)) {
				cout << "Found match" << endl;
				(*iter)->clickOn();
				return true;
			}
		}
		return false;
	}
#endif