#ifndef FishingSpot_cpp
#define FishingSpot_cpp
	#include "FishingSpot.h"

	FishingSpot::FishingSpot() {
	    unique_ptr<Scene> scene(new Scene());
	    select.reset(new Select(0));
		dialog.reset(new Dialog());
		goodDialog.push_back("Net");

		windowFilter.reset(new WindowFilter());
	    bubblesRange.reset(new RangeFilter());
	    bubblesRange->lowHue = 106;
	    bubblesRange->highHue = 109;
	    bubblesRange->highSaturation = 45;
	    bubblesRange->lowValue = 200;

	    waveRange.reset(new RangeFilter());
	    waveRange->lowHue = 107;
	    waveRange->highHue = 110;
	    waveRange->lowSaturation = 110;
	    waveRange->highSaturation = 114;
	    waveRange->lowValue = 160;
	    waveRange->highValue = 200;

	    waveErode.reset(new ErodeFilter());
	    waveErode->kernelSize = 2;

	    waveDilate.reset(new ErodeFilter());
	    waveDilate->kernelSize = 30;
	    waveDilate->mode = "DILATE";

	    waterSpotRange.reset(new RangeFilter());
	    waterSpotRange->lowHue = 104;
	    waterSpotRange->highHue = 109;
	    waterSpotRange->lowSaturation = 135;
	    waterSpotRange->highSaturation = 159;
	    waterSpotRange->lowValue = 129;
	    waterSpotRange->highValue = 162;

	    waterSpotErode.reset(new ErodeFilter());
	    waterSpotErode->kernelSize = 1;

	    waterSpotDilate.reset(new ErodeFilter());
	    waterSpotDilate->kernelSize = 30;
	    waterSpotDilate->mode = "DILATE";

	}

	FishingSpot::~FishingSpot() {
	}

	bool FishingSpot::use()
	{
	    cv::Mat bubbles, wave, waterSpot;
	    int count;

        scene->redraw();
        bubbles = scene->getSceneImage();
        bubbles = windowFilter->apply(bubbles);
        bubbles = bubblesRange->apply(bubbles);

        scene->redraw();
        wave = scene->getSceneImage();
        wave = windowFilter->apply(wave);
        wave = waveRange->apply(wave);
        wave = waveErode->apply(wave);
        wave = waveDilate->apply(wave);
        cv::bitwise_and(bubbles, wave, bubbles);

        scene->redraw();
        waterSpot = scene->getSceneImage();
        waterSpot = windowFilter->apply(waterSpot);
        waterSpot = waterSpotRange->apply(waterSpot);
        waterSpot = waterSpotErode->apply(waterSpot);
        waterSpot = waterSpotDilate->apply(waterSpot);
        cv::bitwise_and(bubbles, waterSpot, bubbles);

        return select->selectDialog(bubbles, goodDialog, badDialog);
	} 
#endif