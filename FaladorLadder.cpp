#ifndef FaladorLadder_cpp
#define FaladorLadder_cpp
	#include "FaladorLadder.h"

	FaladorLadder::FaladorLadder() {
		minGuessDistance = 50;
	    unique_ptr<Scene> scene(new Scene());
		dialog.reset(new Dialog());
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
	    cv::Mat ladder;
	    cv::Mat ladderStructure;
	    cv::Mat blackness;
	    cv::Mat grayness;
        scene->redraw();
        ladder = scene->getSceneImage();
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
        double minVal, maxVal; 
        cv::Point minLoc, maxLoc;
        while(true) {
            minMaxLoc( ladder, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat() );
            if (maxVal > 100) {
                glideToPosition(maxLoc.x, maxLoc.y);
                click(RIGHT_CLICK);
                dialog->initialize();
                if (dialog->match("Climb")) {
                	dialog->select("Climb");
    				nsleep(5000);
                	return true;
                } else if (dialog->match("Clim")) {
                	dialog->select("Clim");
    				nsleep(5000);
                	return true;
                } else {
                	dialog->select("Cancel");
                	cv::circle(ladder, maxLoc, minGuessDistance, CV_RGB(0,0,0), -1);
                }
            } else {
                break;
            }
        }
        return false;
	} 
#endif