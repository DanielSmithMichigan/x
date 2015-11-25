#ifndef Object_h
#define Object_h
	#include "utilities.h"
	#include "interface.h"

	using namespace std;

	class Object {
		protected:
			cv::Mat &sceneImage;
		public:
			Object(cv::Mat &sceneImage);
			void initialize();
			void draw(const cv::Scalar &borderColor = CV_RGB(255, 0, 0), int borderWidth = 3);
			void clickOn(int button=1);
			int width;
			int height;
			cv::Point center;
			cv::Point topLeft;
	};
#endif