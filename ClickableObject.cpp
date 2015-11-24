#ifndef ClickableObject_cpp
#define ClickableObject_cpp
	#include "ClickableObject.h"

	ClickableObject::ClickableObject(string imageLocation, cv::Mat &sceneImage, const cv::Scalar& borderColor) 
	: imageLocation(imageLocation), sceneImage(sceneImage), borderColor(borderColor) {

	}

	void ClickableObject::initialize() {
		this->image = cv::imread(this->imageLocation, CV_LOAD_IMAGE_COLOR);
		if (!this->image.data) {
			string error = "Image at this location did not load: " + this->imageLocation;
			cout << error;
			throw(error);
		}
		this->coordinates = findImage(this->sceneImage, this->image, this->borderColor, this->imageLocation);
	}

	void ClickableObject::clickOn(int button) {
		if (this->coordinates.x == -1
			|| this->coordinates.y == -1) {
			string error = "Object not initialized, or could not be found in scene: " + this->imageLocation;
			cout << error << endl;
			throw(error);
		}
		moveToPosition(this->coordinates.x, this->coordinates.y);
		click(button);
	}
#endif