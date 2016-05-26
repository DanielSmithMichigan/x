#ifndef Object_cpp
#define Object_cpp
	#include "Object.h"

	Object::Object() {
		center = cv::Point(-1, -1);
		topLeft = cv::Point(-1, -1);
		clickMarginHeight = 0;
		clickMarginWidth = 0;
		height = -1;
		width = -1;
		unique_ptr<Scene> scene (new Scene());
	}

	Object::~Object() {
		
	}

	bool Object::initialize() {
		center = cv::Point(topLeft.x + (width / 2), topLeft.y + (height/ 2));
		return true;
	}

	void Object::draw(const cv::Scalar &borderColor, int borderWidth) {

		rectangle(scene->getSceneImage(), 
			topLeft, 
			cv::Point(topLeft.x + width , topLeft.y + height), 
			borderColor, 
			borderWidth);
	}

	cv::Mat Object::getImage() {
		if (center.x == -1
			|| center.y == -1) {
			string error = "Object not initialized, or could not be found in scene";
			cout << error << endl;
			throw(error);
		}
		return ImageFromDisplay(width, height, topLeft.x, topLeft.y);
	}

	void Object::saveImage(string name) {
		imwrite(name, getImage());
	}

	void Object::clickOn(int button) {
		if (center.x == -1
			|| center.y == -1) {
			string error = "Object not initialized, or could not be found in scene";
			cout << error << endl;
			throw(error);
		}
		int x = randomBetween(topLeft.x + clickMarginWidth, topLeft.x + width - clickMarginWidth);
		int y = randomBetween(topLeft.y + clickMarginHeight, topLeft.y + height - clickMarginHeight);
		glideToPosition(x, y);
		click(button);
	}

	bool Object::waitForMatch(int retryInterval, int numRetries)
	{
		if (--numRetries < 0) {
			return false;
		}

		scene->redraw();
		if (!initialize()) {
			nsleep(retryInterval);
			waitForMatch(retryInterval, numRetries);
		} else {
			return true;
		}
	}
#endif