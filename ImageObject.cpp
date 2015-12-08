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

	bool ImageObject::initialize() 
	{
		match();
		Object::initialize();
		return topLeft.x != -1 && topLeft.y != -1;
	}

	bool ImageObject::match() 
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
		return found;
	}
#endif