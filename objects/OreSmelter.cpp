#ifndef OreSmelter_cpp
#define OreSmelter_cpp
	#include "OreSmelter.h"

	OreSmelter::OreSmelter() {
	    unique_ptr<Scene> scene(new Scene());
		select.reset(new Select(0));
		goodDialog.push_back("Withdr");

		windowFilter.reset(new WindowFilter());

	    purpleBarRange.reset(new RangeFilter());
	    purpleBarRange->lowHue = 139;
	    purpleBarRange->highHue = 141;
	    purpleBarRange->lowSaturation = 91;
	    purpleBarRange->highSaturation = 95;
	    purpleBarRange->lowValue = 117;
	    purpleBarRange->highValue = 232;

	    purpleBarErode.reset(new ErodeFilter());
	    purpleBarErode->kernelSize = 1;

	    purpleBarDilate.reset(new ErodeFilter());
	    purpleBarDilate->kernelSize = 30;
	    purpleBarDilate->mode = "DILATE";

	    blueBarRange.reset(new RangeFilter());
	    blueBarRange->lowHue = 73;
	    blueBarRange->highHue = 80;
	    blueBarRange->lowSaturation = 55;
	    blueBarRange->highSaturation = 615;
	    blueBarRange->lowValue = 117;
	    blueBarRange->highValue = 232;

	    blueBarErode.reset(new ErodeFilter());
	    blueBarErode->kernelSize = 1;

	    blueBarDilate.reset(new ErodeFilter());
	    blueBarDilate->kernelSize = 30;
	    blueBarDilate->mode = "DILATE";
	}

	OreSmelter::~OreSmelter() {
	}

	bool OreSmelter::use()
	{
	    cv::Mat blueBar, purpleBar;

        scene->redraw();
        blueBar = scene->getSceneImage();
        blueBar = windowFilter->apply(blueBar);
        blueBar = blueBarRange->apply(blueBar);
        blueBar = blueBarErode->apply(blueBar);
        scene->redraw();
        purpleBar = scene->getSceneImage();
        purpleBar = purpleBarRange->apply(purpleBar);
        purpleBar = purpleBarErode->apply(purpleBar);
        purpleBar = purpleBarDilate->apply(purpleBar);
        cv::bitwise_and(blueBar, purpleBar, blueBar);
        return select->selectDialog(blueBar, goodDialog, badDialog);
	} 
#endif