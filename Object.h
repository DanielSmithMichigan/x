#ifndef Object_h
#define Object_h
	#include "Scene.h"
	#include "imageUtilities.h"
	#include "interface.h"

	using namespace std;

	class Object {
		protected:
			unique_ptr<Scene> scene;
		public:
			Object();
			virtual ~Object();
			void initialize();
			void draw(const cv::Scalar &borderColor = CV_RGB(255, 0, 0), int borderWidth = 3);
			void clickOn(int button=1);
			int width;
			int height;
			int clickMarginHeight;
			int clickMarginWidth;
			cv::Point center;
			cv::Point topLeft;
	};
#endif