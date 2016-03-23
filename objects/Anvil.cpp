#ifndef Anvil_cpp
#define Anvil_cpp
	#include "Anvil.h"

	Anvil::Anvil() {
	    unique_ptr<Scene> scene(new Scene());
		select.reset(new Select(0));
		goodDialog.push_back("Smith");

		windowFilter.reset(new WindowFilter());

	    anvilRange.reset(new RangeFilter());
	    anvilRange->lowHue = 15;
	    anvilRange->highHue = 28;
	    anvilRange->lowSaturation = 61;
	    anvilRange->highSaturation = 73;
	    anvilRange->lowValue = 68;
	    anvilRange->highValue = 79;

	    anvilErode.reset(new ErodeFilter());
	    anvilErode->kernelSize = 1;

	    anvilPieceRange.reset(new RangeFilter());
	    anvilPieceRange->lowHue = 12;
	    anvilPieceRange->highHue = 12;
	    anvilPieceRange->lowSaturation = 52;
	    anvilPieceRange->highSaturation = 62;
	    anvilPieceRange->lowValue = 92;
	    anvilPieceRange->highValue = 111;

	    anvilPieceErode.reset(new ErodeFilter());
	    anvilPieceErode->kernelSize = 1;

	    anvilPieceDilate.reset(new ErodeFilter());
	    anvilPieceDilate->kernelSize = 23;
	    anvilPieceDilate->mode = "DILATE";
	}

	Anvil::~Anvil() {
	}

	bool Anvil::use()
	{
	    cv::Mat anvil, anvilPiece;

        scene->redraw();
        anvil = scene->getSceneImage();
        anvil = windowFilter->apply(anvil);
        anvil = anvilRange->apply(anvil);
        anvil = anvilErode->apply(anvil);

        scene->redraw();
        anvilPiece = scene->getSceneImage();
        anvilPiece = windowFilter->apply(anvilPiece);
        anvilPiece = anvilPieceRange->apply(anvilPiece);
        anvilPiece = anvilPieceErode->apply(anvilPiece);
        anvilPiece = anvilPieceDilate->apply(anvilPiece);

        cv::bitwise_and(anvil, anvilPiece, anvil);
        return select->selectDialog(anvil, goodDialog, badDialog);
	} 
#endif