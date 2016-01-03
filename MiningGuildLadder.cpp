#ifndef MiningGuildLadder_cpp
#define MiningGuildLadder_cpp
	#include "MiningGuildLadder.h"

	MiningGuildLadder::MiningGuildLadder() {
	    unique_ptr<Scene> scene(new Scene());
		select.reset(new Select());
        goodDialog.push_back("Climb");
        goodDialog.push_back("Clim");

        windowFilter.reset(new WindowFilter());
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
        ladder = windowFilter->apply(ladder);
        ladder = ladderRange->apply(ladder);
        ladder = ladderErode->apply(ladder);
        return select->selectDialog(ladder, goodDialog, badDialog);
	} 
#endif