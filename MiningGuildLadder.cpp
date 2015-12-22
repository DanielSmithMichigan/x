#ifndef MiningGuildLadder_cpp
#define MiningGuildLadder_cpp
	#include "MiningGuildLadder.h"

	MiningGuildLadder::MiningGuildLadder() {
		minGuessDistance = 50;
	    unique_ptr<Scene> scene(new Scene());
		dialog.reset(new Dialog());
	    ladderRange.reset(new RangeFilter());
	    ladderRange->lowHue = 18;
	    ladderRange->highHue = 24;
	    ladderRange->lowSaturation = 51;
	    ladderRange->highSaturation = 68;
        ladderRange->lowValue = 64;
        ladderRange->highValue = 104;

	    ladderErode.reset(new ErodeFilter());
	    ladderErode->kernelSize = 1;
	}

	MiningGuildLadder::~MiningGuildLadder() {
	}

	bool MiningGuildLadder::use()
	{
	    cv::Mat ladder;
        scene->redraw();
        ladder = scene->getSceneImage();
        ladder = ladderRange->apply(ladder);
        ladder = ladderErode->apply(ladder);
        double minVal, maxVal; 
        cv::Point minLoc, maxLoc;
        while(true) {
            minMaxLoc( ladder, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat() );
            if (maxVal > 100) {
                glideToPosition(maxLoc.x, maxLoc.y);
                click(RIGHT_CLICK);
                dialog->initialize();
                if (dialog->match("Climb")) {
                	dialog->select("Climb");
                    nsleep(5000);
                	return true;
                } else if (dialog->match("Clim")) {
                	dialog->select("Clim");
                    nsleep(5000);
                	return true;
                } else {
                	dialog->select("Cancel");
                	cv::circle(ladder, maxLoc, minGuessDistance, CV_RGB(0,0,0), -1);
                }
            } else {
                break;
            }
        }
        return false;
	} 
#endif