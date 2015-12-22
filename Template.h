#ifndef template_h
#define template_h
	#include "Scene.h"

	using namespace std;

	class Template {
		private:
		protected:
			virtual cv::Point performMatch(cv::Mat &imgScene);
			virtual cv::Mat preprocessImage(cv::Mat &imageIn, string imageName);
			cv::Mat imgObject;
		public:
			Template();
			Template(string imageLocation);
			Template(cv::Mat i);
			virtual ~Template();
			virtual cv::Mat prepareForRetry(cv::Mat sceneImage);
		    bool match(cv::Mat &sceneImage);
		    int width;
		    int height;
			int retries;
			int retryInterval;
			double rotation;
			double scaling;
			float threshold;
			bool logFailure;
		    cv::Point topLeft;
			unique_ptr<Scene> scene;
	};
#endif