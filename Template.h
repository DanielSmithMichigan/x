#ifndef template_h
#define template_h
	#include "Scene.h"
	

	using namespace std;

	class Template {
		private:
			int retries;
			float threshold;
			int retryInterval;
			cv::Mat imgObject;
			cv::Point performMatch(cv::Mat &imgScene);
		protected:
			virtual cv::Mat preprocessImage(cv::Mat &imageIn);
		public:
			Template(string imageLocation);
		    bool match(cv::Mat &imgScene);
		    int width;
		    int height;
		    cv::Point topLeft;
	};
#endif