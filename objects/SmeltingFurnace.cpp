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
	    redRange->lowHue = 2;
	    redRange->highHue = 3;
	    redRange->lowSaturation = 234;
	    redRange->lowValue = 160;

	    redErode.reset(new ErodeFilter());
	    redErode->kernelSize = 1;

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
	    hammerRange->lowHue = 16;
	    hammerRange->highHue = 17;
	    hammerRange->lowSaturation = 93;
	    hammerRange->highSaturation = 96;
	    hammerRange->lowValue = 19;
	    hammerRange->highValue = 93;

	    hammerErode.reset(new ErodeFilter());
	    hammerErode->kernelSize = 1;

	    hammerDilate.reset(new ErodeFilter());
	    hammerDilate->kernelSize = 30;
	    hammerDilate->mode = "DILATE";
	}

	SmeltingFurnace::~SmeltingFurnace() {
	}

	bool SmeltingFurnace::use()
	{
	    cv::Mat red, gate, hammer;

        scene->redraw();
        red = scene->getSceneImage();
        red = windowFilter->apply(red);
        red = redRange->apply(red);
        red = redErode->apply(red);
        
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

        if (select->selectDialog(red, goodDialog, badDialog)) {
        	if (actionButton->waitForMatch()) {
        		actionButton->clickOn();
        		return true;
        	}
        }
        return false;
	} 
#endif