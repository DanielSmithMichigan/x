#ifndef ImageObject_h
#define ImageObject_h
	#include "Object.h"
	#include "Scene.h"
	#include "Template.h"

	using namespace std;

	class ImageObject : public Object {
		private:
			string imageLocation;
			cv::Mat image;
		public:
			ImageObject(string imageLocation);
			void initialize();
	};
#endif