#ifndef template_h
#define template_h
	#include "Scene.h"

	using namespace std;

	class Template {
		private:
		protected:
			virtual cv::Point performMatch(cv::Mat &imgScene) = 0;
			int retries;
			int retryInterval;
		public:
			Template();
			virtual void prepareForRetry();
		    bool match();
		    int width;
		    int height;
		    cv::Point topLeft;
		    Scene* scene;
	};
#endif