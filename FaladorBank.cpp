#ifndef FaladorBank_cpp
#define FaladorBank_cpp
	#include "FaladorBank.h"

	FaladorBank::FaladorBank() {
		minGuessDistance = 50;
	    unique_ptr<Scene> scene(new Scene());
		dialog.reset(new Dialog());

		windowFilter.reset(new WindowFilter());
	    noteRange.reset(new RangeFilter());

	    noteRange->lowHue = 10;
	    noteRange->highHue = 15;
	    noteRange->highSaturation = 100;

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
	    matRange->lowHue = 25;
	    matRange->highHue = 33;
	    matRange->lowSaturation = 19;
	    matRange->highSaturation = 25;
	    matRange->lowValue = 180;
	    matRange->highValue = 223;

	    matErode.reset(new ErodeFilter());
	    matErode->kernelSize = 1;

	    matDilate.reset(new ErodeFilter());
	    matDilate->kernelSize = 50;
	    matDilate->mode = "DILATE";

	    matTwoRange.reset(new RangeFilter());
	    matTwoRange->lowHue = 0;
	    matTwoRange->highHue = 180;
	    matTwoRange->lowSaturation = 0;
	    matTwoRange->highSaturation = 2;
	    matTwoRange->lowValue = 250;
	    matTwoRange->highValue = 255;
	}

	FaladorBank::~FaladorBank() {
	}

	bool FaladorBank::use()
	{
	    cv::Mat note, bankFloor, mat;
        scene->redraw();
        note = scene->getSceneImage();
        note = windowFilter->apply(note);
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
        cv::bitwise_and(note, mat, note);
        scene->redraw();
        mat = scene->getSceneImage();
        mat = matTwoRange->apply(mat);
        mat = matErode->apply(mat);
        mat = matDilate->apply(mat);
        cv::bitwise_and(note, mat, note);

        scene->redraw();
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

	bool FaladorBank::open() {
		cout << "Checking if bank is open" << endl;
		unique_ptr<Template> bankCornerTemplate(new Template("../images/BankCorner.png"));
		bankCornerTemplate->threshold = .05;
		bankCornerTemplate->retries = 5;
		bankCornerTemplate->retryInterval = 200;
		unique_ptr<ImageObject> bankCorner(new ImageObject());
		bankCorner->addTemplate(move(bankCornerTemplate));
		bankCorner->initialize();
		return bankCorner->match();
	}

	bool FaladorBank::close() {
		cout << "Checking if bank is open" << endl;
		scene->redraw();
		unique_ptr<ImageObject> bankCorner(new ImageObject("../images/BankCloseButton.png"));
		bankCorner->initialize();
		if (bankCorner->match()) {
			bankCorner->clickOn();
			return true;
		}
		return false;
	}
#endif