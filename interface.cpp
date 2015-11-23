#include "interface.h"

void moveToPosition(int x, int y) {
    Display *display = XOpenDisplay(NULL);
	
	if(display == NULL)
	{
		fprintf(stderr, "Error opening display");
		exit(EXIT_FAILURE);
	}

 	Window root = DefaultRootWindow(display);
    XWarpPointer(display, None, root, 0, 0, 0, 0, x, y);
	XFlush(display);
    XCloseDisplay(display);
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