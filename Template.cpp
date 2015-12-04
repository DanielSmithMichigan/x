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
		scene = new Scene();
	}

	void Template::prepareForRetry()
	{
	}

	bool Template::match()
	{
		int retriesAvailable = this->retries;
		topLeft = performMatch(scene->getSceneImage());
		while(--retriesAvailable > 0 && (topLeft.x == -1 || topLeft.y == -1)) {
			cout << "Matching template retry: " << retriesAvailable << endl;
			topLeft = performMatch(scene->getSceneImage());
		}

		if (topLeft.x == -1 || topLeft.y == -1) {
			return false;
		}
		
		return true;
	}

#endif