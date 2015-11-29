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
		public:
			Template(cv::Mat &imgScene);
		    cv::Point match(cv::Mat &imgObject);
	};
#endif