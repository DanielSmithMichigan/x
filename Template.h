#ifndef template_h
#define template_h
	#include "Scene.h"

	using namespace std;

	class Template {
		private:
		protected:
			virtual cv::Point performMatch(cv::Mat &imgScene) = 0;
			int retryInterval;
		public:
			Template();
			virtual ~Template();
			virtual void prepareForRetry();
		    bool match(cv::Mat &sceneImage);
		    int width;
		    int height;
			int retries;
			double rotation;
			double scaling;
		    cv::Point topLeft;
			unique_ptr<Scene> scene;
	};
#endif