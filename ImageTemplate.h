#ifndef imagetemplate_h
#define imagetemplate_h
	#include "Template.h"

	using namespace std;

	class ImageTemplate : public Template {
		private:
			float threshold;
			cv::Mat imgObject;
			virtual cv::Point performMatch(cv::Mat &imgScene);
			void prepareForRetry();
		protected:
			virtual cv::Mat preprocessImage(cv::Mat &imageIn);
		public:
			bool logFailure;
			ImageTemplate(string imageLocation);
			virtual ~ImageTemplate();
	};
#endif