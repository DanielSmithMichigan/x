#ifndef magic_cpp
#define magic_cpp
	#include "Magic.h"
	#define THREE_KEY 65548

	Magic::Magic() {
	}

	Magic::~Magic() {

	}

	void Magic::run() {
		while(true) {
			cout << "PRESSING" << endl;
			nsleep(1000);
			keypress(THREE_KEY, 25);
		}
	}

#endif