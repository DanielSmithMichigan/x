#ifndef PottersWheel_cpp
#define PottersWheel_cpp
	#include "PottersWheel.h"

	PottersWheel::PottersWheel() {
	    mouldButton.reset(new ImageObject("../images/MouldButton.png"));
	    unique_ptr<Scene> scene(new Scene());
		select.reset(new Select());
		goodDialog.push_back("Form");

		windowFilter.reset(new WindowFilter());

	    wheelRange.reset(new RangeFilter());
	    wheelRange->highHue = 20;
	    wheelRange->lowSaturation = 19;
	    wheelRange->highSaturation = 24;
	    wheelRange->lowValue = 159;
	    wheelRange->highValue = 171;

	    wheelErode.reset(new ErodeFilter());
	    wheelErode->kernelSize = 2;

	    boxRange.reset(new RangeFilter());
	    boxRange->lowHue = 16;
	    boxRange->highHue = 18;
	    boxRange->lowSaturation = 152;
	    boxRange->highSaturation = 158;
	    boxRange->lowValue = 98;
	    boxRange->highValue = 125;

	    boxErode.reset(new ErodeFilter());
	    boxErode->kernelSize = 1;

	    boxDilate.reset(new ErodeFilter());
	    boxDilate->kernelSize = 15;
	    boxDilate->mode = "DILATE";
	}

	PottersWheel::~PottersWheel() {
	}

	bool PottersWheel::use()
	{
	    cv::Mat wheel, box, table;

        scene->redraw();
        wheel = scene->getSceneImage();
        wheel = windowFilter->apply(wheel);
        wheel = wheelRange->apply(wheel);
        wheel = wheelErode->apply(wheel);

        scene->redraw();
        box = scene->getSceneImage();
        box = windowFilter->apply(box);
        box = boxRange->apply(box);
        box = boxErode->apply(box);
        box = boxDilate->apply(box);
        cv::bitwise_and(wheel, box, wheel);

        if (select->selectDialog(wheel, goodDialog, badDialog)) {
        	scene->redraw();
        	if (mouldButton->initialize()) {
        		mouldButton->clickOn();
        		return true;
        	}
        }
        return false;
	} 
#endif