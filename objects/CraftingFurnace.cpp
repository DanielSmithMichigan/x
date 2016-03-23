#ifndef CraftingFurnace_cpp
#define CraftingFurnace_cpp
	#include "CraftingFurnace.h"

	CraftingFurnace::CraftingFurnace() {
	    fireButton.reset(new ImageObject("../images/FireButton.png"));
	    unique_ptr<Scene> scene(new Scene());
		select.reset(new Select(4000));
		goodDialog.push_back("Fire");

		windowFilter.reset(new WindowFilter());

	    ringRange.reset(new RangeFilter());
	    ringRange->lowHue = 17;
	    ringRange->highHue = 22;
	    ringRange->lowSaturation = 53;
	    ringRange->highSaturation = 69;
	    ringRange->lowValue = 45;
	    ringRange->highValue = 84;

	    ringErode.reset(new ErodeFilter());
	    ringErode->kernelSize = 1;

	    fireRange.reset(new RangeFilter());
	    fireRange->lowHue = 3;
	    fireRange->highHue = 5;
	    fireRange->lowSaturation = 234;
	    fireRange->highValue = 99;

	    fireErode.reset(new ErodeFilter());
	    fireErode->kernelSize = 1;

	    fireDilate.reset(new ErodeFilter());
	    fireDilate->kernelSize = 15;
	    fireDilate->mode = "DILATE";
	}

	CraftingFurnace::~CraftingFurnace() {
	}

	bool CraftingFurnace::use()
	{
	    cv::Mat ring, fire;

        scene->redraw();
        ring = scene->getSceneImage();
        ring = windowFilter->apply(ring);
        ring = ringRange->apply(ring);
        ring = ringErode->apply(ring);

        scene->redraw();
        fire = scene->getSceneImage();
        fire = windowFilter->apply(fire);
        fire = fireRange->apply(fire);
        fire = fireErode->apply(fire);
        fire = fireDilate->apply(fire);
        cv::bitwise_and(fire, ring, ring);

        if (select->selectDialog(ring, goodDialog, badDialog)) {
        	scene->redraw();
        	if (fireButton->initialize()) {
        		fireButton->clickOn();
        		return true;
        	}
        }
        return false;
	} 
#endif