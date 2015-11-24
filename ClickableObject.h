#ifndef ClickableObject_h
#define ClickableObject_h
	#include "utilities.h"
	#include "interface.h"

	using namespace std;

	class ClickableObject {
		private:
			string imageLocation;
			const cv::Scalar &borderColor;
			cv::Point coordinates;
			cv::Mat sceneImage;
			cv::Mat image;
		public:
			ClickableObject(string imageLocation, cv::Mat &sceneImage, const cv::Scalar& borderColor);
			void initialize();
			void clickOn(int button=1);
	};
#endif