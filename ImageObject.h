#ifndef ImageObject_h
#define ImageObject_h
	#include "Object.h"

	using namespace std;

	class ImageObject : public Object {
		private:
			string imageLocation;
			cv::Mat image;
		public:
			ImageObject(string imageLocation, cv::Mat &sceneImage);
			void initialize();
	};
#endif