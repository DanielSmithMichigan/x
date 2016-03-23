#ifndef ArmorDeposit_cpp
#define ArmorDeposit_cpp
	#include "ArmorDeposit.h"

	ArmorDeposit::ArmorDeposit() {
	    unique_ptr<Scene> scene(new Scene());
		select.reset(new Select(0));
		goodDialog.push_back("Deposit");
		goodDialog.push_back("Oeposit");

		windowFilter.reset(new WindowFilter());

	    blacknessRange.reset(new RangeFilter());
	    blacknessRange->lowSaturation = 26;
	    blacknessRange->highSaturation = 45;
	    blacknessRange->lowValue = 22;
	    blacknessRange->highValue = 24;

	    blacknessErode.reset(new ErodeFilter());
	    blacknessErode->kernelSize = 4;

	    handRailRange.reset(new RangeFilter());
	    handRailRange->lowHue = 16;
	    handRailRange->highHue = 19;
	    handRailRange->lowSaturation = 92;
	    handRailRange->highSaturation = 99;
	    handRailRange->highValue = 37;
	    handRailRange->highValue = 85;

	    handRailErode.reset(new ErodeFilter());
	    handRailErode->kernelSize = 1;

	    handRailDilate.reset(new ErodeFilter());
	    handRailDilate->kernelSize = 50;
	    handRailDilate->mode = "DILATE";
	}

	ArmorDeposit::~ArmorDeposit() {
	}

	bool ArmorDeposit::use()
	{
	    cv::Mat blackness, handRail;

        scene->redraw();
        blackness = scene->getSceneImage();
        blackness = windowFilter->apply(blackness);
        blackness = blacknessRange->apply(blackness);
        blackness = blacknessErode->apply(blackness);

        scene->redraw();
        handRail = scene->getSceneImage();
        handRail = windowFilter->apply(handRail);
        handRail = handRailRange->apply(handRail);
        handRail = handRailErode->apply(handRail);
        handRail = handRailDilate->apply(handRail);

        cv::bitwise_not(handRail, handRail);

        cv::bitwise_and(blackness, handRail, blackness);

        return select->selectDialog(blackness, goodDialog, badDialog);
	} 
#endif