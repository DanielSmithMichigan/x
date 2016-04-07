#ifndef ActionButton_cpp
#define ActionButton_cpp
	#include "ActionButton.h"

	ActionButton::ActionButton() {
	}

	ActionButton::~ActionButton() {
	}

	bool ActionButton::initialize()
	{
		unique_ptr<ImageObject> left(new ImageObject("../images/ActionButtonLeft.png"));
		if(!left->initialize()) {
			return false;
		}
		topLeft.x = left->topLeft.x + left->width;
		topLeft.y = left->topLeft.y;
		width = 80;
		height = left->height;
		unique_ptr<ImageObject> right(new ImageObject("../images/ActionButtonRight.png"));
		if (!right->initialize()) {
			return true;
		}
		width = right->topLeft.x - topLeft.x;
		Object::initialize();
		return true;
	} 
#endif