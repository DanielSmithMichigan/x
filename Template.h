#ifndef template_h
#define template_h
	#include <opencv2/core/core.hpp>
	#include <opencv2/imgproc/imgproc.hpp>
	#include <opencv2/highgui/highgui.hpp>

	using namespace std;

	class Template {
		private:
			int retries;
			float threshold;
			int retryInterval;

			cv::Mat &imgObject;
			cv::Point performMatch(cv::Mat &imgScene);
		public:
			Template(cv::Mat &imgObject);
		    cv::Point match(cv::Mat &imgScene);
	};
#endif