#ifndef Rock_cpp
#define Rock_cpp
	#include "Rock.h"

	Rock::Rock() {
	    unique_ptr<Scene> scene(new Scene());
		select.reset(new Select(50));
		goodDialog.push_back("Mine");
		badDialog.push_back("MineRocks");
        windowFilter.reset(new WindowFilter());

	    rockBaseRange.reset(new RangeFilter());
	    rockBaseRange->lowHue = 21;
	    rockBaseRange->highHue = 23;
	    rockBaseRange->lowSaturation = 148;
	    rockBaseRange->highSaturation = 153;

	    rockBaseDungeonRange.reset(new RangeFilter());
	    rockBaseDungeonRange->lowHue = 19;
	    rockBaseDungeonRange->highHue = 23;
	    rockBaseDungeonRange->lowSaturation = 184;

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

	    ironRange.reset(new RangeFilter());
	    ironRange->lowHue = 8;
	    ironRange->highHue = 9;
	    ironRange->lowSaturation = 100;
	    ironRange->highValue = 130;

	    clayRange.reset(new RangeFilter());
	    clayRange->lowHue = 18;
	    clayRange->highHue = 20;
	    clayRange->lowSaturation = 108;
	    clayRange->highSaturation = 125;
	    clayRange->lowValue = 195;

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

	bool Rock::use(string oreType, map<string, bool> flags)
	{
		cv::Mat rockBase, ore;

        scene->redraw();
        rockBase = scene->getSceneImage();
        rockBase = windowFilter->apply(rockBase);
        if (flags["DUNGEON_ROCKS"]) {
        	rockBase = rockBaseDungeonRange->apply(rockBase);
        } else {
        	rockBase = rockBaseRange->apply(rockBase);
        }
        rockBase = rockBaseErode->apply(rockBase);
        rockBase = rockBaseDilate->apply(rockBase);

        scene->redraw();
    	ore = scene->getSceneImage();
        ore = windowFilter->apply(ore);
        if (oreType == "COAL") {
        	ore = coalRange->apply(ore);
        } else if (oreType == "MITHRIL") {
        	ore = mithrilRange->apply(ore);
        } else if (oreType == "ADAM") {
        	ore = adamRange->apply(ore);
        } else if (oreType == "IRON") {
        	ore = ironRange->apply(ore);
        } else if (oreType == "CLAY") {
        	ore = clayRange->apply(ore);
        } else if (oreType == "COAL_OR_MITHRIL") {
        	ore = mithrilRange->apply(ore);
        	scene->redraw();
        	cv::Mat coal = scene->getSceneImage();
        	coal = coalRange->apply(coal);
        	cv::bitwise_or(ore, coal, ore);
        }

        cv::bitwise_and(ore, rockBase, ore);
        return select->selectDialog(ore, goodDialog, badDialog);
	} 
#endif