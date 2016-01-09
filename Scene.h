#ifndef Scene_h
#define Scene_h
	#include "imageUtilities.h"
	#include "utilities.h"
	#include <map>
	#define SCENE_WIDTH 1600
	#define SCENE_HEIGHT 900

	using namespace std;

	class Scene {
		private:
			static cv::Mat image;
		public:
			Scene();
			virtual ~Scene();
			static void getScreen();
			static void redraw();
			static cv::Mat &getSceneImage();
			static void draw();
	};
#endif