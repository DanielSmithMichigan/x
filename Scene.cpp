#ifndef Scene_cpp
#define Scene_cpp
	#include "Scene.h"

	cv::Mat Scene::image;

	Scene::Scene() {
	}

	void Scene::redraw() {
		getScreen();
	}

	void Scene::getScreen() {
		nsleep(50);		
		image = ImageFromDisplay(SCENE_WIDTH, SCENE_HEIGHT);
	}

	void Scene::draw() {
		imshow("W", Scene::image);
		cv::waitKey(100000);
	}

	cv::Mat &Scene::getSceneImage() {
		return Scene::image;
	}
#endif