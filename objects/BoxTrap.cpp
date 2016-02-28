#ifndef BoxTrap_cpp
#define BoxTrap_cpp
	#include "BoxTrap.h"

	BoxTrap::BoxTrap() {
	    unique_ptr<Scene> scene(new Scene());
		dialog.reset(new Dialog());

		maxArea = 30.0;

		windowFilter.reset(new WindowFilter());
	    boxRange.reset(new RangeFilter());
	    boxRange->lowHue = 18;
	    boxRange->highHue = 22;
	    boxRange->lowSaturation = 81;
	    boxRange->highSaturation = 99;
	    boxRange->lowValue = 130;

	    fallenBoxRange.reset(new RangeFilter());
	    fallenBoxRange->lowHue = 26;
	    fallenBoxRange->highHue = 29;
	    fallenBoxRange->lowSaturation = 80;
	    fallenBoxRange->highSaturation = 110;
	    fallenBoxRange->lowValue = 100;

	    boxErode.reset(new ErodeFilter());
	    boxErode->kernelSize = 1;

	    rockRange.reset(new RangeFilter());
	    rockRange->lowSaturation = 0;
	    rockRange->highSaturation = 26;
	    rockRange->lowValue = 130;

	    rockErode.reset(new ErodeFilter());
	    rockErode->kernelSize = 1;

	    rockDilate.reset(new ErodeFilter());
	    rockDilate->kernelSize = 50;
	    rockDilate->mode = "DILATE";

	    stickRange.reset(new RangeFilter());
	    stickRange->lowHue = 19;
	    stickRange->highHue = 21;
	    stickRange->lowSaturation = 130;
	    stickRange->highSaturation = 153;
	    stickRange->lowValue = 92;
	    stickRange->highValue = 131;

	    fallenStickRange.reset(new RangeFilter());
	    fallenStickRange->lowHue = 27;
	    fallenStickRange->highHue = 29;
	    fallenStickRange->lowSaturation = 100;
	    fallenStickRange->highSaturation = 169;
	    fallenStickRange->lowValue = 100;

	    stickDilate.reset(new ErodeFilter());
	    stickDilate->kernelSize = 50;
	    stickDilate->mode = "DILATE";
	}

	BoxTrap::~BoxTrap() {
	}

	bool BoxTrap::use()
	{
	    cv::Mat box, fallenBox, rock, stick, fallenStick;

        scene->redraw();
        box = scene->getSceneImage();
        box = windowFilter->apply(box);
        box = boxRange->apply(box);
        box = boxErode->apply(box);
        scene->redraw();
        rock = scene->getSceneImage();
        rock = rockRange->apply(rock);
        rock = rockErode->apply(rock);
        rock = rockDilate->apply(rock);
        cv::bitwise_and(box, rock, box);
        scene->redraw();
        stick = scene->getSceneImage();
        stick = windowFilter->apply(stick);
        stick = stickRange->apply(stick);
        stick = stickDilate->apply(stick);
        cv::bitwise_and(box, stick, box);

        scene->redraw();
        fallenBox = scene->getSceneImage();
        fallenBox = windowFilter->apply(fallenBox);
        fallenBox = fallenBoxRange->apply(fallenBox);
        fallenBox = boxErode->apply(fallenBox);
        cv::bitwise_and(fallenBox, rock, fallenBox);
        scene->redraw();
        fallenStick = scene->getSceneImage();
        fallenStick = windowFilter->apply(fallenStick);
        fallenStick = fallenStickRange->apply(fallenStick);
        fallenStick = stickDilate->apply(fallenStick);
        cv::bitwise_and(fallenBox, fallenStick, fallenBox);

        cv::bitwise_or(fallenBox, box, box);

        vector<cv::KeyPoint> keypoints;
        cv::SimpleBlobDetector::Params params;
		params.filterByInertia = false;
		params.filterByConvexity = false;
		params.filterByColor = false;
		params.filterByCircularity = false;
        cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params); 
		detector->detect( box, keypoints );
		for (int i=0; i<keypoints.size(); i++){
			cout << "SIZE: " << keypoints[i].size << endl;
			if (keypoints[i].size <= maxArea) {
				glideToPosition(keypoints[i].pt.x, keypoints[i].pt.y);
				click(RIGHT_CLICK);
                dialog->initialize();
                if (dialog->select("Lay")) {
        			nsleep(4000);
                	return true;
                } else if (dialog->select("Check")) {
        			nsleep(4000);
                	return true;
                } else if (dialog->select("Rebuild")) {
					nsleep(5200);
					return true;
                } else {
                	dialog->select("Cancel");
                	continue;
                }
			}
		}
        return false;
	} 
#endif