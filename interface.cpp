#ifndef interface_cpp
#define interface_cpp
	#include "interface.h"

	int currMouseX;
	int currMouseY;

	void moveToPosition(int x, int y) {
	    Display *display = XOpenDisplay(NULL);
		
		if(display == NULL)
		{
			fprintf(stderr, "Error opening display");
			exit(EXIT_FAILURE);
		}

	 	Window root = DefaultRootWindow(display);
	    XWarpPointer(display, None, root, 0, 0, 0, 0, x, y);
	    currMouseX = x;
	    currMouseY = y;
		XFlush(display);
	    XCloseDisplay(display);
	}

	void glideToPosition(int x, int y, int marginErr, long interval, int maxStepSize) {
		int diffX = x - currMouseX;
		diffX = absMax(diffX, maxStepSize);
		int diffY = y - currMouseY;
		diffY = absMax(diffY, maxStepSize);
		int nextX = randomBetween(diffX + currMouseX - (marginErr / 2), diffX + currMouseX + (marginErr / 2));
		int nextY = randomBetween(diffY + currMouseY - (marginErr / 2), diffY + currMouseY + (marginErr / 2));
		moveToPosition(nextX, nextY);
		nsleep(interval);
		if (distanceTo(currMouseX, currMouseY, x, y) > marginErr) {
			glideToPosition(x, y, marginErr, interval);
		}
	}


	void click(int button) {
	    Display *display = XOpenDisplay(NULL);
		
		if(display == NULL)
		{
			fprintf(stderr, "Error opening display");
			exit(EXIT_FAILURE);
		}
		int down = XTestFakeButtonEvent(display, button, true, 0);
		int up = XTestFakeButtonEvent(display, button, false, 0);
	    XFlush(display);
	}
#endif