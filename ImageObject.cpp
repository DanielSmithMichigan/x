#ifndef ImageObject_cpp
#define ImageObject_cpp
	#include "ImageObject.h"

	ImageObject::ImageObject()
	: Object() {
	}

	ImageObject::ImageObject(string imageLocation)
	{
		templates.push_back(new Template(imageLocation));
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
				(*iter)->match(scene->getSceneImage())) {
				height = (*iter)->height;
				width = (*iter)->width;
				topLeft = (*iter)->topLeft;
				found = true;
			}
		}
		if (!found) {
			cout << "Could not find template in image" << endl;
			throw("NO_TEMPLATE");
		}
	}
#endif