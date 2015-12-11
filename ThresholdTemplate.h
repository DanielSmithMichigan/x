#ifndef thresholdtemplate_h
#define thresholdtemplate_h
	#include "ImageTemplate.h"
	
	using namespace std;

	class ThresholdTemplate : public ImageTemplate {
		private:
			int thresholdType;
			int threshold;
			int maxValue;
		    cv::Mat preprocessImage(cv::Mat &imageIn);
		public:
			ThresholdTemplate(string imageLocation);
			virtual ~ThresholdTemplate();
	};
#endif