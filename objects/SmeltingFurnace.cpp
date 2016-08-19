#ifndef SmeltingFurnace_cpp
#define SmeltingFurnace_cpp
	#include "SmeltingFurnace.h"

	SmeltingFurnace::SmeltingFurnace() {
		actionButton.reset(new ActionButton());
	    scene.reset(new Scene());
		select.reset(new Select(0));
		goodDialog.push_back("Smelt");

		windowFilter.reset(new WindowFilter());

	    redRange.reset(new RangeFilter());
	    redRange->lowHue = 0;
	    redRange->highHue = 3;
	    redRange->lowSaturation = 232;
	    redRange->lowValue = 160;

	    redErode.reset(new ErodeFilter());
	    redErode->kernelSize = 1;

	    redRoofDilate.reset(new ErodeFilter());
	    redRoofDilate->mode = "DILATE";
	    redRoofDilate->kernelSize = 10;

	    redRoofShiftFilter.reset(new ShiftFilter());
	    redRoofShiftFilter->offsetY = 78;

	    gateRange.reset(new RangeFilter());
	    gateRange->lowHue = 30;
	    gateRange->highHue = 30;
	    gateRange->lowSaturation = 15;
	    gateRange->highSaturation = 30;
	    gateRange->lowValue = 45;
	    gateRange->highValue = 72;

	    gateErode.reset(new ErodeFilter());
	    gateErode->kernelSize = 1;

	    gateDilate.reset(new ErodeFilter());
	    gateDilate->kernelSize = 30;
	    gateDilate->mode = "DILATE";


	    hammerRange.reset(new RangeFilter());
	    hammerRange->lowHue = 15;
	    hammerRange->highHue = 17;
	    hammerRange->lowSaturation = 90;
	    hammerRange->highSaturation = 96;
	    hammerRange->lowValue = 19;
	    hammerRange->highValue = 101;

	    hammerErode.reset(new ErodeFilter());
	    hammerErode->kernelSize = 1;

	    hammerDilate.reset(new ErodeFilter());
	    hammerDilate->kernelSize = 30;
	    hammerDilate->mode = "DILATE";


	    bricksRange.reset(new RangeFilter());
	    bricksRange->lowHue = 20;
	    bricksRange->highHue = 26;
	    bricksRange->lowSaturation = 59;
	    bricksRange->highSaturation = 62;
	    bricksRange->lowValue = 134;
	    bricksRange->highValue = 166;

	    bricksErode.reset(new ErodeFilter());
	    bricksErode->kernelSize = 1;

	    bricksDilate.reset(new ErodeFilter());
	    bricksDilate->kernelSize = 25;
	    bricksDilate->mode = "DILATE";
	}

	SmeltingFurnace::~SmeltingFurnace() {
	}

	bool SmeltingFurnace::use()
	{
	    cv::Mat red, redRoof, gate, hammer, bricks;

        scene->redraw();
        red = scene->getSceneImage();
        red = windowFilter->apply(red);
        red = redRange->apply(red);
        red = redErode->apply(red);

        scene->redraw();
        redRoof = scene->getSceneImage();
        redRoof = windowFilter->apply(redRoof);
        redRoof = redRange->apply(redRoof);
        redRoof = redRoofShiftFilter->apply(redRoof);
        redRoof = redRoofDilate->apply(redRoof);
        cv::bitwise_and(red, redRoof, red);
        
        scene->redraw();
        gate = scene->getSceneImage();
        gate = windowFilter->apply(gate);
        gate = gateRange->apply(gate);
        gate = gateErode->apply(gate);
        gate = gateDilate->apply(gate);
        cv::bitwise_and(gate, red, red);
        
        scene->redraw();
        hammer = scene->getSceneImage();
        hammer = windowFilter->apply(hammer);
        hammer = hammerRange->apply(hammer);
        hammer = hammerErode->apply(hammer);
        hammer = hammerDilate->apply(hammer);
        cv::bitwise_and(hammer, red, red);
        
        scene->redraw();
        bricks = scene->getSceneImage();
        bricks = windowFilter->apply(bricks);
        bricks = bricksRange->apply(bricks);
        bricks = bricksErode->apply(bricks);
        bricks = bricksDilate->apply(bricks);
        cv::bitwise_and(bricks, red, red);
        
        if (select->selectDialog(red, goodDialog, badDialog)) {
        	if (actionButton->waitForMatch()) {
        		actionButton->clickOn();
        		return true;
        	}
        }
        return false;
	} 
#endif