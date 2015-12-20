#ifndef FaladorBank_cpp
#define FaladorBank_cpp
	#include "FaladorBank.h"

	FaladorBank::FaladorBank() {
		minGuessDistance = 10;
	    unique_ptr<Scene> scene(new Scene());
		dialog.reset(new Dialog());
	    noteRange.reset(new RangeFilter());
	    noteRange->lowHue = 13;
	    noteRange->highHue = 13;
	    noteRange->lowSaturation = 63;
	    noteRange->highSaturation = 65;

	    noteErode.reset(new ErodeFilter());
	    noteErode->kernelSize = 1;

	    bankFloorRange.reset(new RangeFilter());
	    bankFloorRange->lowHue = 104;
	    bankFloorRange->highHue = 106;
	    bankFloorRange->lowSaturation = 56;
	    bankFloorRange->highSaturation = 65;
	    bankFloorRange->lowValue = 110;

	    bankFloorErode.reset(new ErodeFilter());
	    bankFloorErode->kernelSize = 1;

	    bankFloorDilate.reset(new ErodeFilter());
	    bankFloorDilate->kernelSize = 50;
	    bankFloorDilate->mode = "DILATE";

	    matRange.reset(new RangeFilter());
	    matRange->lowHue = 29;
	    matRange->highHue = 33;
	    matRange->lowSaturation = 19;
	    matRange->highSaturation = 25;
	    matRange->lowValue = 201;
	    matRange->highValue = 203;

	    matErode.reset(new ErodeFilter());
	    matErode->kernelSize = 1;

	    matDilate.reset(new ErodeFilter());
	    matDilate->kernelSize = 50;
	    matDilate->mode = "DILATE";
	}

	FaladorBank::~FaladorBank() {
	}

	bool FaladorBank::use()
	{
	    cv::Mat note;
	    cv::Mat bankFloor;
	    cv::Mat mat;
        scene->redraw();
        note = scene->getSceneImage();
        note = noteRange->apply(note);
        note = noteErode->apply(note);
        scene->redraw();
        bankFloor = scene->getSceneImage();
        bankFloor = bankFloorRange->apply(bankFloor);
        bankFloor = bankFloorErode->apply(bankFloor);
        bankFloor = bankFloorDilate->apply(bankFloor);
        cv::bitwise_and(note, bankFloor, note);
        scene->redraw();
        mat = scene->getSceneImage();
        mat = matRange->apply(mat);
        mat = matErode->apply(mat);
        mat = matDilate->apply(mat);
        scene->redraw();
        cv::bitwise_and(note, mat, note);
        double minVal, maxVal; 
        cv::Point minLoc, maxLoc;
        while(true) {
            minMaxLoc( note, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat() );
            if (maxVal > 100) {
                glideToPosition(maxLoc.x, maxLoc.y);
                click(RIGHT_CLICK);
                dialog->initialize();
                if (dialog->match("Bank")) {
                	dialog->select("Bank");
                	return true;
                } else {
                	dialog->select("Cancel");
                	cv::circle(note, maxLoc, minGuessDistance, CV_RGB(0,0,0), -1);
                }
            } else {
                break;
            }
        }
        return false;
	} 
#endif