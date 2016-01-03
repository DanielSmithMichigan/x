#ifndef FaladorLadder_cpp
#define FaladorLadder_cpp
	#include "FaladorLadder.h"

	FaladorLadder::FaladorLadder() {
	    unique_ptr<Scene> scene(new Scene());
		select.reset(new Select());
		goodDialog.push_back("Climb");
		goodDialog.push_back("Clim");

		windowFilter.reset(new WindowFilter());
	    ladderRange.reset(new RangeFilter());
	    ladderRange->lowHue = 18;
	    ladderRange->highHue = 22;
	    ladderRange->lowSaturation = 119;
	    ladderRange->highSaturation = 180;
	    ladderRange->lowValue = 116;
	    ladderRange->highValue = 160;

	    ladderErode.reset(new ErodeFilter());
	    ladderErode->kernelSize = 1;

	    ladderStructureRange.reset(new RangeFilter());
	    ladderStructureRange->lowHue = 13;
	    ladderStructureRange->highHue = 17;
	    ladderStructureRange->lowSaturation = 120;
	    ladderStructureRange->highSaturation = 140;
	    ladderStructureRange->lowValue = 105;
	    ladderStructureRange->highValue = 138;

	    ladderStructureErode.reset(new ErodeFilter());
	    ladderStructureErode->kernelSize = 1;

	    ladderStructureDilate.reset(new ErodeFilter());
	    ladderStructureDilate->kernelSize = 37;
	    ladderStructureDilate->mode = "DILATE";

	    blacknessRange.reset(new RangeFilter());
	    blacknessRange->lowHue = 0;
	    blacknessRange->highHue = 180;
	    blacknessRange->lowSaturation = 0;
	    blacknessRange->highSaturation = 21;
	    blacknessRange->lowValue = 0;
	    blacknessRange->highValue = 45;

	    blacknessErode.reset(new ErodeFilter());
	    blacknessErode->kernelSize = 2;

	    blacknessDilate.reset(new ErodeFilter());
	    blacknessDilate->kernelSize = 41;
	    blacknessDilate->mode = "DILATE";

	    graynessRange.reset(new RangeFilter());
	    graynessRange->lowHue = 13;
	    graynessRange->highHue = 20;
	    graynessRange->lowSaturation = 21;
	    graynessRange->highSaturation = 30;
	    graynessRange->lowValue = 76;
	    graynessRange->highValue = 95;

	    graynessErode.reset(new ErodeFilter());
	    graynessErode->kernelSize = 4;

	    graynessDilate.reset(new ErodeFilter());
	    graynessDilate->kernelSize = 41;
	    graynessDilate->mode = "DILATE";
	}

	FaladorLadder::~FaladorLadder() {
	}

	bool FaladorLadder::use()
	{
	    cv::Mat ladder, ladderStructure, blackness, grayness;

        scene->redraw();
        ladder = scene->getSceneImage();
        ladder = windowFilter->apply(ladder);
        ladder = ladderRange->apply(ladder);
        ladder = ladderErode->apply(ladder);
        scene->redraw();
        ladderStructure = scene->getSceneImage();
        ladderStructure = ladderStructureRange->apply(ladderStructure);
        ladderStructure = ladderStructureErode->apply(ladderStructure);
        ladderStructure = ladderStructureDilate->apply(ladderStructure);
        cv::bitwise_and(ladder, ladderStructure, ladder);
        scene->redraw();
        grayness = scene->getSceneImage();
        grayness = graynessRange->apply(grayness);
        grayness = graynessErode->apply(grayness);
        grayness = graynessDilate->apply(grayness);
        scene->redraw();
        blackness = scene->getSceneImage();
        blackness = blacknessRange->apply(blackness);
        blackness = blacknessErode->apply(blackness);
        blackness = blacknessDilate->apply(blackness);
        cv::bitwise_or(blackness, grayness, blackness);
        cv::bitwise_and(ladder, blackness, ladder);
        ladder = ladderErode->apply(ladder);
        if (select->selectDialog(ladder, goodDialog, badDialog)) {
			glideToPosition(1081, 180);
			click(LEFT_CLICK);
			nsleep(1000);
			return true;
        }
        return false;
	} 
#endif