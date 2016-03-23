#ifndef Chest_cpp
#define Chest_cpp
	#include "Chest.h"

	Chest::Chest() {
	    unique_ptr<Scene> scene(new Scene());
	    select.reset(new Select(0));
		dialog.reset(new Dialog());
		goodDialog.push_back("UseBank");

		maxArea = 30.0;

		windowFilter.reset(new WindowFilter());
	    blacknessRange.reset(new RangeFilter());
	    blacknessRange->highHue = 22;
	    blacknessRange->lowSaturation = 70;
	    blacknessRange->highSaturation = 110;
	    blacknessRange->lowValue = 23;
	    blacknessRange->highValue = 26;

	    blacknessErode.reset(new ErodeFilter());
	    blacknessErode->kernelSize = 1;

	    blacknessDilate.reset(new ErodeFilter());
	    blacknessDilate->kernelSize = 25;
	    blacknessDilate->mode = "DILATE";

	    rockRange.reset(new RangeFilter());
	    rockRange->lowHue = 18;
	    rockRange->highHue = 30;
	    rockRange->lowSaturation = 89;
	    rockRange->highSaturation = 95;
	    rockRange->lowValue = 179;

	    rockErode.reset(new ErodeFilter());
	    rockErode->kernelSize = 1;

	    rockDilate.reset(new ErodeFilter());
	    rockDilate->kernelSize = 50;
	    rockDilate->mode = "DILATE";

	    chestRange.reset(new RangeFilter());
	    chestRange->lowHue = 15;
	    chestRange->highHue = 18;
	    chestRange->lowSaturation = 88;
	    chestRange->highSaturation = 95;
	    chestRange->lowValue = 70;
	    chestRange->highValue = 200;

	    chestErode.reset(new ErodeFilter());
	    chestErode->kernelSize = 1;

	    chestDilate.reset(new ErodeFilter());
	    chestDilate->kernelSize = 10;
	    chestDilate->mode = "DILATE";

	    lockRange.reset(new RangeFilter());
	    lockRange->lowHue = 90;
	    lockRange->highHue = 113;
	    lockRange->lowSaturation = 19;
	    lockRange->highSaturation = 33;
	    lockRange->lowValue = 130;
	    lockRange->highValue = 147;

	}

	Chest::~Chest() {
	}

	bool Chest::use()
	{
	    cv::Mat blackness, rock, chest, lock;

        scene->redraw();
        blackness = scene->getSceneImage();
        blackness = windowFilter->apply(blackness);
        blackness = blacknessRange->apply(blackness);
        blackness = blacknessErode->apply(blackness);
        blackness = blacknessDilate->apply(blackness);
        
        scene->redraw();
        rock = scene->getSceneImage();
        rock = windowFilter->apply(rock);
        rock = rockRange->apply(rock);
        rock = rockErode->apply(rock);
        rock = rockDilate->apply(rock);
        cv::bitwise_and(blackness, rock, blackness);

        scene->redraw();
        chest = scene->getSceneImage();
        chest = windowFilter->apply(chest);
        chest = chestRange->apply(chest);
        chest = chestErode->apply(chest);
        chest = chestDilate->apply(chest);
        cv::bitwise_and(blackness, chest, blackness);

        scene->redraw();
        lock = scene->getSceneImage();
        lock = windowFilter->apply(lock);
        lock = lockRange->apply(lock);
        cv::bitwise_and(blackness, lock, blackness);

        return select->selectDialog(blackness, goodDialog, badDialog);
	} 

	void Chest::storeAll()
	{
		unique_ptr<ImageObject> storeAllButton(new ImageObject("../images/BankStoreAll.png"));
		storeAllButton->initialize();
		storeAllButton->clickOn();
	}

	void Chest::loadPresetOne()
	{
		unique_ptr<ImageObject> presetOne(new ImageObject("../images/BankPresetOne.png"));
		presetOne->initialize();
		presetOne->clickOn();
	}

	bool Chest::open() {
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
#endif