#ifndef imageUtilities_h
#define imageUtilities_h
	#include <stdio.h>
	#include <iostream>
	#include <opencv2/core/core.hpp>
	#include <opencv2/imgproc/imgproc.hpp>
	#include <opencv2/highgui/highgui.hpp>
	#include <opencv2/features2d.hpp>
	#include <opencv2/text.hpp>
    #include <opencv2/xfeatures2d/nonfree.hpp>
	#include <opencv2/calib3d/calib3d.hpp>
	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <unistd.h>
	#include <algorithm> 
	#include <stdio.h>
	#include <ctype.h>

	using namespace std;
	bool imagesEqual(cv::Mat a, cv::Mat b, float threshold = .025);
	cv::Mat ImageFromDisplay(int Width, int Height, int x = 0, int y = 0);
	void findImage(cv::Mat &img_scene, cv::Mat &img_object, cv::Point &topLeft, float threshold = .25);
#endif