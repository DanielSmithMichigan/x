#ifndef surftemplate_h
#define surftemplate_h
	#include "ImageTemplate.h"
	
	using namespace std;

	class SurfTemplate : public ImageTemplate {
		private:
		    cv::Point performMatch(cv::Mat &imageIn);
		    cv::Ptr<cv::xfeatures2d::SURF> surf;
		    cv::FlannBasedMatcher matcher;
		    double distance;
		    int minHessian;
		public:
			SurfTemplate(cv::Mat imgObj);
			virtual ~SurfTemplate();
	};
#endif