#ifndef Sink_cpp
#define Sink_cpp
	#include "Sink.h"

	Sink::Sink() {
	    softenButton.reset(new ImageObject("../images/SoftenButton.png"));
	    unique_ptr<Scene> scene(new Scene());
		select.reset(new Select(2000));
		goodDialog.push_back("UseClaySink");

		windowFilter.reset(new WindowFilter());

	    waterRange.reset(new RangeFilter());
	    waterRange->lowHue = 109;
	    waterRange->highHue = 111;
	    waterRange->lowSaturation = 116;
	    waterRange->highSaturation = 127;
	    waterRange->lowValue = 220;
	    waterRange->highValue = 255;

	    waterErode.reset(new ErodeFilter());
	    waterErode->kernelSize = 3;

	    sinkRange.reset(new RangeFilter());
	    sinkRange->lowHue = 15;
	    sinkRange->highHue = 18;
	    sinkRange->lowSaturation = 57;
	    sinkRange->highSaturation = 65;
	    sinkRange->highValue = 99;
	    sinkRange->highValue = 164;

	    sinkErode.reset(new ErodeFilter());
	    sinkErode->kernelSize = 3;

	    sinkDilate.reset(new ErodeFilter());
	    sinkDilate->kernelSize = 30;
	    sinkDilate->mode = "DILATE";
	}

	Sink::~Sink() {
	}

	void Sink::beforeSelect() {
		unique_ptr<Inventory> inventory(new Inventory());
		inventory->initialize();

		cv::Mat clay = cv::imread("../images/inventoryItems/Clay.png");
		cv::Point match = inventory->firstMatch(clay);
		inventory->clickItem(match.x, match.y, LEFT_CLICK);
		nsleep(250);
	}

	bool Sink::use()
	{
	    cv::Mat water, sink;

        scene->redraw();
        water = scene->getSceneImage();
        water = windowFilter->apply(water);
        water = waterRange->apply(water);
        water = waterErode->apply(water);

        scene->redraw();
        sink = scene->getSceneImage();
        sink = windowFilter->apply(sink);
        sink = sinkRange->apply(sink);
        sink = sinkErode->apply(sink);
        sink = sinkDilate->apply(sink);

        cv::bitwise_and(water, sink, water);
        if (select->selectDialog(water, goodDialog, badDialog, beforeSelect)) {
        	scene->redraw();
        	if (softenButton->initialize()) {
        		softenButton->clickOn();
        		return true;
        	}
        }
        return false;
	} 
#endif