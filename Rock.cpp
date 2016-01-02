#ifndef Rock_cpp
#define Rock_cpp
	#include "Rock.h"

	Rock::Rock() {
		oreType = "COAL";
		minGuessDistance = 50;
	    unique_ptr<Scene> scene(new Scene());
		dialog.reset(new Dialog());

		cornerFilter.reset(new CornerFilter());

	    rockBaseRange.reset(new RangeFilter());
	    rockBaseRange->lowHue = 21;
	    rockBaseRange->highHue = 23;
	    rockBaseRange->lowSaturation = 148;
	    rockBaseRange->highSaturation = 153;

	    rockBaseErode.reset(new ErodeFilter());
	    rockBaseErode->kernelSize = 2;

	    rockBaseDilate.reset(new ErodeFilter());
	    rockBaseDilate->kernelSize = 10;
	    rockBaseDilate->mode = "DILATE";

	    coalRange.reset(new RangeFilter());
	    coalRange->lowHue = 28;
	    coalRange->highHue = 31;
	    coalRange->lowSaturation = 0;
	    coalRange->highSaturation = 50;
	    coalRange->lowValue = 0;
	    coalRange->highValue = 40;

	    mithrilRange.reset(new RangeFilter());
	    mithrilRange->lowHue = 119;
	    mithrilRange->highHue = 120;
	    mithrilRange->lowSaturation = 92;
	    mithrilRange->highSaturation = 95;
	    mithrilRange->lowValue = 140;

	    adamRange.reset(new RangeFilter());
	    adamRange->lowHue = 59;
	    adamRange->highHue = 62;
	    adamRange->lowSaturation = 59;
	    adamRange->highSaturation = 62;
	    adamRange->lowValue = 100;

	    oreErode.reset(new ErodeFilter());
	    oreErode->kernelSize = 2;

	    oreDilate.reset(new ErodeFilter());
	    oreDilate->kernelSize = 10;
	    oreDilate->mode = "DILATE";
	}

	Rock::~Rock() {
	}

	bool Rock::use()
	{
		cv::Point playerLocation;
	    unique_ptr<ImageObject> worldMap (new ImageObject("../images/WorldMap.png"));
	    if (worldMap->initialize()) {
	        playerLocation = cv::Point(worldMap->topLeft.x - 442, worldMap->topLeft.y + 263);
	    } else {
	        unique_ptr<ImageObject> helpButton (new ImageObject("../images/HelpButton.png"));
	        if (helpButton->initialize()) {
	            playerLocation = cv::Point(helpButton->topLeft.x - 442, helpButton->topLeft.y + 295);
	        } else {
	            string error = "Could not locate map";
	            cout << error << endl;
	            throw(error);
	        }
	    }

		cv::Mat corners, rockBase, ore;
        scene->redraw();
        corners = scene->getSceneImage();
        corners = cornerFilter->apply(corners);

        scene->redraw();
        rockBase = scene->getSceneImage();
        rockBase = rockBaseRange->apply(rockBase);
        rockBase = rockBaseErode->apply(rockBase);
        rockBase = rockBaseDilate->apply(rockBase);

        scene->redraw();
    	ore = scene->getSceneImage();
        if (oreType == "COAL") {
        	ore = coalRange->apply(ore);
        } else if (oreType == "MITHRIL") {
        	ore = mithrilRange->apply(ore);
        } else if (oreType == "ADAM") {
        	ore = adamRange->apply(ore);
        }
        ore = oreErode->apply(ore);
        ore = oreDilate->apply(ore);

        cv::bitwise_and(ore, corners, ore);
        cv::bitwise_and(ore, rockBase, ore);

        cv::Point closestLocation;
        bool found = false;
        double minDistance = -1;
        double currDistance = -1;
        while(true) {
        	found = false;
        	minDistance = -1;
			for( int x = 0; x < ore.cols ; x++ )
			{ 
				for( int y = 0; y < ore.rows; y++ )
				{
					if( (int) ore.at<float>(y,x) > 100)
					{
						currDistance = distanceTo(x, y, playerLocation.x, playerLocation.y);
						if (minDistance == -1 || currDistance < minDistance) {
							closestLocation = cv::Point(x, y);
							found = true;
						}
					}
				}
			}
            if (found) {
                glideToPosition(closestLocation.x, closestLocation.y);
                click(RIGHT_CLICK);
                dialog->initialize();
                if (dialog->match("MineRocks")) {
                	dialog->select("Cancel");
                	cv::circle(ore, closestLocation, minGuessDistance, CV_RGB(0,0,0), -1);
                } else if (dialog->match("Mine")) {
                	dialog->select("Mine");
                	return true;
                } else {
                	dialog->select("Cancel");
                	cv::circle(ore, closestLocation, minGuessDistance, CV_RGB(0,0,0), -1);
                }
            } else {
                break;
            }
        }
        return false;
	} 
#endif