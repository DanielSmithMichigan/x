#ifndef BankScreen_cpp
#define BankScreen_cpp
	#include "BankScreen.h"

	BankScreen::BankScreen() {
		scene.reset(new Scene());
	}

	BankScreen::~BankScreen() {
	}


	void BankScreen::storeAll()
	{
		unique_ptr<ImageObject> storeAllButton(new ImageObject("../images/BankStoreAll.png"));
		storeAllButton->initialize();
		storeAllButton->clickOn();
	}

	void BankScreen::loadPresetOne()
	{
		unique_ptr<ImageObject> presetOne(new ImageObject("../images/BankPresetOne.png"));
		presetOne->initialize();
		presetOne->clickOn();
	}

	bool BankScreen::open() {
		cout << "Checking if bank is open" << endl;
		scene->redraw();
		unique_ptr<Template> bankCornerTemplate(new Template("../images/BankCorner.png"));
		bankCornerTemplate->threshold = .05;
		bankCornerTemplate->retries = 5;
		bankCornerTemplate->retryInterval = 200;
		unique_ptr<ImageObject> bankCorner(new ImageObject());
		bankCorner->addTemplate(move(bankCornerTemplate));
		return bankCorner->initialize();
	}

	bool BankScreen::close() {
		cout << "Checking if bank is open" << endl;
		scene->redraw();
		unique_ptr<ImageObject> bankCorner(new ImageObject("../images/BankCloseButton.png"));
		if (bankCorner->initialize()) {
			bankCorner->clickOn();
			return true;
		}
		return false;
	}
#endif