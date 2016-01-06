#ifndef DungeonEntrance_cpp
#define DungeonEntrance_cpp
	#include "DungeonEntrance.h"

	DungeonEntrance::DungeonEntrance() {
	    unique_ptr<Scene> scene(new Scene());
		select.reset(new Select());
		goodDialog.push_back("Enter");
		goodDialog.push_back("Exit");

		windowFilter.reset(new WindowFilter());
	    symbolRange.reset(new RangeFilter());
	    symbolRange->lowHue = 2;
	    symbolRange->highHue = 4;
	    symbolRange->lowSaturation = 145;
	    symbolRange->lowValue = 94;

	    symbolErode.reset(new ErodeFilter());
	    symbolErode->kernelSize = 1;

	    entranceOneRange.reset(new RangeFilter());
	    entranceOneRange->lowHue = 34;
	    entranceOneRange->highHue = 41;
	    entranceOneRange->lowSaturation = 14;
	    entranceOneRange->highSaturation = 27;
	    entranceOneRange->lowValue = 21;
	    entranceOneRange->highValue = 76;

	    entranceOneErode.reset(new ErodeFilter());
	    entranceOneErode->kernelSize = 1;

	    entranceOneDilate.reset(new ErodeFilter());
	    entranceOneDilate->kernelSize = 41;
	    entranceOneDilate->mode = "DILATE";

	    entranceTwoRange.reset(new RangeFilter());
	    entranceTwoRange->lowHue = 30;
	    entranceTwoRange->highHue = 36;
	    entranceTwoRange->lowSaturation = 15;
	    entranceTwoRange->highSaturation = 27;
	    entranceTwoRange->lowValue = 60;
	    entranceTwoRange->highValue = 200;

	    entranceTwoErode.reset(new ErodeFilter());
	    entranceTwoErode->kernelSize = 1;

	    entranceTwoDilate.reset(new ErodeFilter());
	    entranceTwoDilate->kernelSize = 41;
	    entranceTwoDilate->mode = "DILATE";
	}

	DungeonEntrance::~DungeonEntrance() {
	}

	bool DungeonEntrance::use()
	{
	    cv::Mat symbol, entranceOne, entranceTwo;

        scene->redraw();
        symbol = scene->getSceneImage();
        symbol = windowFilter->apply(symbol);
        symbol = symbolRange->apply(symbol);
        scene->redraw();
        entranceOne = scene->getSceneImage();
        entranceOne = entranceOneRange->apply(entranceOne);
        entranceOne = entranceOneErode->apply(entranceOne);
        entranceOne = entranceOneDilate->apply(entranceOne);
        cv::bitwise_and(symbol, entranceOne, symbol);
        scene->redraw();
        entranceTwo = scene->getSceneImage();
        entranceTwo = entranceTwoRange->apply(entranceTwo);
        entranceTwo = entranceTwoErode->apply(entranceTwo);
        entranceTwo = entranceTwoDilate->apply(entranceTwo);
        cv::bitwise_and(entranceTwo, symbol, entranceTwo);
        return select->selectDialog(symbol, goodDialog, badDialog);
	} 
#endif