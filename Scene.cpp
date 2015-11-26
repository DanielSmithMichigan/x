#ifndef Scene_cpp
#define Scene_cpp
	#include "Scene.h"

	cv::Mat Scene::image;

	Scene::Scene() {
	}

	void Scene::redraw() {
		cout << "Redrawing scene" << endl;
		nsleep(200);
		Scene::image = ImageFromDisplay(SCENE_WIDTH, SCENE_HEIGHT);
	}

	cv::Mat& Scene::getSceneImage() {
		return Scene::image;
	}
#endif