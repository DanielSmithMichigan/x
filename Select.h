#ifndef Select_h
#define Select_h
	#include "Scene.h"
	#include "Dialog.h"
	#include "ImageObject.h"
	#include "MapButton.h"

	using namespace std;

	class Select {
		private:
			cv::Point playerLocation;
			unique_ptr<Dialog> dialog;
			unique_ptr<MapButton> mapButton;
			int minGuessDistance;
			int minWaitTime;
		public:
			bool selectDialog(cv::Mat selectableImage, vector<string> goodDialog, vector<string> badDialog);
			void initialize();
			Select(int minWaitTime = 5000, int minGuessDistance = 50);
			virtual ~Select();
	};
#endif