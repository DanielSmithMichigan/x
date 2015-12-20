#ifndef template_h
#define template_h
	#include "Scene.h"

	using namespace std;

	class Template {
		private:
			float threshold;
		protected:
			virtual cv::Point performMatch(cv::Mat &imgScene);
			virtual cv::Mat preprocessImage(cv::Mat &imageIn, string imageName);
			int retryInterval;
			cv::Mat imgObject;
		public:
			Template();
			Template(string imageLocation);
			Template(cv::Mat i);
			virtual ~Template();
			virtual void prepareForRetry();
		    bool match(cv::Mat &sceneImage);
		    int width;
		    int height;
			int retries;
			double rotation;
			double scaling;
			bool logFailure;
		    cv::Point topLeft;
			unique_ptr<Scene> scene;
	};
#endif