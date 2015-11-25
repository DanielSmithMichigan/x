#ifndef utilities_h
#define utilities_h
	#include <stdio.h>
	#include <iostream>
	#include <opencv2/core/core.hpp>
	#include <opencv2/imgproc/imgproc.hpp>
	#include <opencv2/highgui/highgui.hpp>
	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <unistd.h>

	using namespace std;

	void initialize();
	cv::Mat ImageFromDisplay(int Width, int Height);
	void findImage(cv::Mat &img_scene, cv::Mat &img_object, cv::Point &topLeft, float threshold = .25);
#endif