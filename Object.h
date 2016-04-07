#ifndef Object_h
#define Object_h
	#include "Scene.h"
	#include "imageUtilities.h"
	#include "interface.h"
	#include <map>

	using namespace std;

	class Object {
		protected:
			unique_ptr<Scene> scene;
		public:
			Object();
			virtual ~Object();
			virtual bool initialize();
			void draw(const cv::Scalar &borderColor = CV_RGB(255, 0, 0), int borderWidth = 3);
			void clickOn(int button=1);
			void saveImage(string name);
			bool waitForMatch(int numRetries = 20);
			cv::Mat getImage();
			int width;
			int height;
			int clickMarginHeight;
			int clickMarginWidth;
			cv::Point center;
			cv::Point topLeft;
	};
#endif