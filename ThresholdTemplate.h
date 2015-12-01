#ifndef thresholdtemplate_h
#define thresholdtemplate_h
	#include "Template.h"
	
	using namespace std;

	class ThresholdTemplate : public Template {
		private:
			int thresholdType;
			int threshold;
			int maxValue;
		    cv::Mat preprocessImage(cv::Mat &imageIn);
		public:
			ThresholdTemplate(string imageLocation);
	};
#endif