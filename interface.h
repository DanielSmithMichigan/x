#ifndef interface_h
#define interface_h
	#include <X11/Xlib.h>
	#include <stdio.h>
	#include <iostream>
	#include <unistd.h>
	#include <stdlib.h>
	#include <string.h>
	#include <unistd.h>
	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <X11/extensions/XTest.h>
	#include <memory>
	#include "utilities.h"
	#define LEFT_CLICK 1
	#define RIGHT_CLICK 3

	using namespace std;

	void moveToPosition(int x, int y);
	void glideToPosition(int x, int y, int marginErr = 3, long interval = 1, int maxStepSize = 2);
	void click(int button);
	void keypress(int button, int holdDuration = 0);
#endif