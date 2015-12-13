#ifndef template_cpp
#define template_cpp
	#include "Template.h"

	Template::Template() 
	{
		retries = 1;
		retryInterval = 200;
		width = -1;
		height = -1;
		topLeft = cv::Point(-1, -1);
		unique_ptr<Scene> scene (new Scene());
	}

	Template::~Template() {

	}

	void Template::prepareForRetry()
	{
	}

	bool Template::match(cv::Mat sceneImage)
	{
		int retriesAvailable = this->retries;
		topLeft = performMatch(sceneImage);
		while(--retriesAvailable > 0 && (topLeft.x == -1 || topLeft.y == -1)) {
			cout << "Matching template retry: " << retriesAvailable << endl;
			prepareForRetry();
			topLeft = performMatch(sceneImage);
		}

		if (topLeft.x == -1 || topLeft.y == -1) {
			return false;
		}
		
		return true;
	}

#endif