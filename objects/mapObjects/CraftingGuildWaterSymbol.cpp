#ifndef CraftingGuildwaterIcon_cpp
#define CraftingGuildWaterSymbol_cpp
	#include "CraftingGuildWaterSymbol.h"

	CraftingGuildWaterSymbol::CraftingGuildWaterSymbol() {
	}

	CraftingGuildWaterSymbol::~CraftingGuildWaterSymbol() {
	}

	bool CraftingGuildWaterSymbol::initialize()
	{
		topLeft.x = -1; topLeft.y = -1;
		unique_ptr<Template> waterIconTemplate(new Template("../images/mapObjects/waterIcon.png"));
		waterIconTemplate->threshold = .025;
	    unique_ptr<ImageObject> waterIcon (new ImageObject());
	    waterIcon->addTemplate(move(waterIconTemplate));
		unique_ptr<Template> miningIconeTemplate(new Template("../images/mapObjects/miningIcon.png"));
		miningIconeTemplate->threshold = .025;
        unique_ptr<ImageObject> miningIcon (new ImageObject());
	    miningIcon->addTemplate(move(miningIconeTemplate));
	    if (topLeft.x == -1 || topLeft.y == -1) {
		    if (waterIcon->initialize()) {
		        topLeft = cv::Point(waterIcon->topLeft.x, waterIcon->topLeft.y);
			    width = waterIcon->width;
			    height = waterIcon->height;
		    } 
		}

	    if (topLeft.x == -1 || topLeft.y == -1) {
	        if (miningIcon->initialize()) {
	            topLeft = cv::Point(miningIcon->topLeft.x - 30, miningIcon->topLeft.y + 13);
			    width = miningIcon->width;
			    height = miningIcon->height;
	        }
	    }
	    if (topLeft.x != -1 && topLeft.y != -1) {
	    	Object::initialize();
	    	return true;
	    }
	    return false;
	} 
	void CraftingGuildWaterSymbol::goToMinesite()
	{
		glideToPosition(topLeft.x + 30, topLeft.y - 13);
		click(LEFT_CLICK);
		nsleep(5000);
	}
	void CraftingGuildWaterSymbol::goToCraftingGuildCenter()
	{
		glideToPosition(topLeft.x, topLeft.y - 13);
		click(LEFT_CLICK);
		nsleep(7000);
	}
#endif