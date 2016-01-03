#ifndef Rock_cpp
#define Rock_cpp
	#include "Rock.h"

	Rock::Rock() {
		oreType = "COAL";
	    unique_ptr<Scene> scene(new Scene());
		select.reset(new Select(50));
		goodDialog.push_back("Mine");
		badDialog.push_back("MineRocks");

	    rockBaseRange.reset(new RangeFilter());
	    rockBaseRange->lowHue = 21;
	    rockBaseRange->highHue = 23;
	    rockBaseRange->lowSaturation = 148;
	    rockBaseRange->highSaturation = 153;

	    rockBaseErode.reset(new ErodeFilter());
	    rockBaseErode->kernelSize = 2;

	    rockBaseDilate.reset(new ErodeFilter());
	    rockBaseDilate->kernelSize = 10;
	    rockBaseDilate->mode = "DILATE";

	    coalRange.reset(new RangeFilter());
	    coalRange->lowHue = 28;
	    coalRange->highHue = 31;
	    coalRange->lowSaturation = 0;
	    coalRange->highSaturation = 50;
	    coalRange->lowValue = 0;
	    coalRange->highValue = 40;

	    mithrilRange.reset(new RangeFilter());
	    mithrilRange->lowHue = 119;
	    mithrilRange->highHue = 120;
	    mithrilRange->lowSaturation = 92;
	    mithrilRange->highSaturation = 95;
	    mithrilRange->lowValue = 140;

	    adamRange.reset(new RangeFilter());
	    adamRange->lowHue = 59;
	    adamRange->highHue = 62;
	    adamRange->lowSaturation = 59;
	    adamRange->highSaturation = 62;
	    adamRange->lowValue = 100;

	    oreErode.reset(new ErodeFilter());
	    oreErode->kernelSize = 2;

	    oreDilate.reset(new ErodeFilter());
	    oreDilate->kernelSize = 10;
	    oreDilate->mode = "DILATE";
	}

	Rock::~Rock() {
	}

	bool Rock::use()
	{
		cv::Mat rockBase, ore;

        scene->redraw();
        rockBase = scene->getSceneImage();
        rockBase = rockBaseRange->apply(rockBase);
        rockBase = rockBaseErode->apply(rockBase);
        rockBase = rockBaseDilate->apply(rockBase);

        scene->redraw();
    	ore = scene->getSceneImage();
        if (oreType == "COAL") {
        	ore = coalRange->apply(ore);
        } else if (oreType == "MITHRIL") {
        	ore = mithrilRange->apply(ore);
        } else if (oreType == "ADAM") {
        	ore = adamRange->apply(ore);
        }

        cv::bitwise_and(ore, rockBase, ore);
        return select->selectDialog(ore, goodDialog, badDialog);
	} 
#endif