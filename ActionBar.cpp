#ifndef ActionBar_cpp
#define ActionBar_cpp
	#include "ActionBar.h"

	ActionBar::ActionBar() {
		scene.reset(new Scene());
		buttons.push_back("Inventory");
		buttons.push_back("Magic");
		for(vector<string>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
			buttonImages[*it + "Selected"] = unique_ptr<ImageObject>(new ImageObject("../images/actionBar/" + *it + "Selected.png", .025));
			buttonImages[*it + "Unselected"] = unique_ptr<ImageObject>(new ImageObject("../images/actionBar/" + *it + "Unselected.png", .025));
		}
	}

	ActionBar::~ActionBar() {
	}

	bool ActionBar::initialize() {
		mode = "OTHER";
		for(vector<string>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
			if (buttonImages[*it + "Selected"]->initialize()) {
				mode = *it;
			}
		}
		cout << "Mode: " << mode << endl;
		return true;
	}

	bool ActionBar::select(string newMode) {
		if (mode == newMode) {
			return true;
		}
		if (buttonImages[newMode + "Unselected"]->initialize()) {
			buttonImages[newMode + "Unselected"]->clickOn(LEFT_CLICK);
			mode = newMode;
			return true;
		}
		return false;
	}

#endif