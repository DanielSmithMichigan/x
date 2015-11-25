#ifndef Object_cpp
#define Object_cpp
	#include "Object.h"

	Object::Object(cv::Mat &sceneImage) 
	: sceneImage(sceneImage) {
		this->center = cv::Point(-1, -1);
		this->topLeft = cv::Point(-1, -1);
		this->height = -1;
		this->width = -1;
	}

	void Object::initialize() {
		this->center = cv::Point(this->topLeft.x + (this->width / 2), this->topLeft.y + (this->height/ 2));
	}

	void Object::draw(const cv::Scalar &borderColor, int borderWidth) {
		rectangle(this->sceneImage, 
			this->topLeft, 
			cv::Point(this->topLeft.x + this->width , this->topLeft.y + this->height), 
			borderColor, 
			borderWidth);
	}

	void Object::clickOn(int button) {
		if (this->center.x == -1
			|| this->center.y == -1) {
			string error = "Object not initialized, or could not be found in scene";
			cout << error << endl;
			throw(error);
		}
		moveToPosition(this->center.x, this->center.y);
		click(button);
	}
#endif