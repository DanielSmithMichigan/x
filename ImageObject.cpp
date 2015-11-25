#ifndef ImageObject_cpp
#define ImageObject_cpp
	#include "ImageObject.h"

	ImageObject::ImageObject(string imageLocation, cv::Mat &sceneImage)
	: Object(sceneImage), imageLocation(imageLocation) {
	}

	void ImageObject::initialize() {
		this->image = cv::imread(this->imageLocation, CV_LOAD_IMAGE_COLOR);
		if (!this->image.data) {
			string error = "Image at this location did not load: " + this->imageLocation;
			cout << error;
			throw(error);
		}
		this->width = this->image.cols;
		this->height = this->image.rows;
		findImage(this->sceneImage, this->image, this->topLeft);
		Object::initialize();
	}
#endif