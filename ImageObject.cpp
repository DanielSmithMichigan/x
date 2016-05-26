#ifndef ImageObject_cpp
#define ImageObject_cpp
	#include "ImageObject.h"

	ImageObject::ImageObject()
	: Object() {
	}

	ImageObject::~ImageObject() {
		vector<unique_ptr<Template>>().swap(templates);
	}

	ImageObject::ImageObject(string imageLocation, float threshold)
	{
		unique_ptr<Template> tmpl(new Template(imageLocation));
		if (threshold != -1) {
			tmpl->threshold = threshold;
		}
		templates.push_back(move(tmpl));
		ImageObject();
	}

	void ImageObject::addTemplate(unique_ptr<Template> tmpl) 
	{
		templates.push_back(move(tmpl));
	}

	bool ImageObject::initialize() 
	{
		topLeft.x = -1;
		topLeft.y = -1;
		match();
		Object::initialize();
		return topLeft.x != -1 && topLeft.y != -1;
	}

	bool ImageObject::match() 
	{
		bool found = false;
		for(std::vector<unique_ptr<Template>>::iterator iter = templates.begin(); iter != templates.end(); ++iter) {
			if (!found &&
				(*iter)->match(scene->getSceneImage())) {
				height = (*iter)->height;
				width = (*iter)->width;
				topLeft = (*iter)->topLeft;
				found = true;
			}
		}
		return found;
	}
#endif