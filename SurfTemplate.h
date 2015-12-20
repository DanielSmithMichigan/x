#ifndef surftemplate_h
#define surftemplate_h
	#include "Template.h"
	
	using namespace std;

	class SurfTemplate : public Template {
		private:
		    cv::Point performMatch(cv::Mat &imageIn);
		    cv::Ptr<cv::xfeatures2d::SURF> surf;
		    cv::FlannBasedMatcher matcher;
		    double distance;
		    double maxScaling;
		    double maxRotation;
		    double maxAngleTolerance;
		    int minHessian;
		public:
			SurfTemplate(cv::Mat imgObj);
			virtual ~SurfTemplate();
	};
#endif