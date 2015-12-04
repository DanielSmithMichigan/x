#ifndef ImageObject_cpp
#define ImageObject_cpp
	#include "ImageObject.h"

	ImageObject::ImageObject()
	: Object() {
	}

	ImageObject::ImageObject(string imageLocation)
	{
		templates.push_back(new ImageTemplate(imageLocation));
		ImageObject();
	}

	void ImageObject::addTemplate(Template* tmpl) 
	{
		templates.push_back(tmpl);
	}

	void ImageObject::initialize() 
	{
		match();
		Object::initialize();
	}

	void ImageObject::match() 
	{
		bool found = false;
		for(std::vector<Template*>::iterator iter = templates.begin(); iter != templates.end(); ++iter) {
			if (!found &&
				(*iter)->match()) {
				height = (*iter)->height;
				width = (*iter)->width;
				topLeft = (*iter)->topLeft;
				found = true;
			}
		}
		if (!found) {
			cout << "Could not find template in image" << endl;
			string numString = std::to_string(randomBetween(1000, 9999));
			cv::imwrite("../log/Scene" + numString + ".png", scene->getSceneImage());
			throw("NO_TEMPLATE");
		}
	}
#endif