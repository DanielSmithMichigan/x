#ifndef surftemplate_cpp
#define surftemplate_cpp
	#include "SurfTemplate.h"
	// using namespace cv;
	// using namespace cv::xfeatures2d;

	SurfTemplate::SurfTemplate(cv::Mat imgObj) : Template(imgObj) {
		distance = .5;
		minHessian = 10;
		maxScaling = .15;
		maxRotation = .05;
		maxAngleTolerance = .15;
		retries = 0;
		surf = cv::xfeatures2d::SURF::create(minHessian);
	}

	cv::Mat SurfTemplate::prepareForRetry(cv::Mat sceneImage) {
		return sceneImage;
	}

	cv::Point SurfTemplate::performMatch(cv::Mat &imgScene) {
		vector<cv::KeyPoint> keypointsScene, keypointsObject; 
		cv::Mat descriptorsScene, descriptorsObject;   
		surf->detect(imgScene, keypointsScene); 
		surf->compute(imgScene, keypointsScene, descriptorsScene);
		surf->detect(imgObject, keypointsObject); 
		surf->compute(imgObject, keypointsObject, descriptorsObject);

		vector<cv::DMatch> matches;
		matcher.match(descriptorsObject, descriptorsScene, matches);

		vector<cv::DMatch> goodMatches;
		for(int i = 0; i < descriptorsObject.rows; i++) {
			if (matches[i].distance < distance) {
				goodMatches.push_back(matches[i]);
			}
		}
		
		vector<cv::Point2f> objPoints,scenePoints;
		for(int i = 0; i < goodMatches.size(); i++) {
			objPoints.push_back(keypointsObject[goodMatches[i].queryIdx].pt);
			scenePoints.push_back(keypointsScene[goodMatches[i].trainIdx].pt);
		}
		cv::Mat H;
		try {
			H = cv::findHomography( objPoints, scenePoints, CV_RANSAC );
		} catch(cv::Exception) {
			cout << "Can't find homography" << endl;
			return cv::Point(-1, -1);
		}

		vector<cv::Point2f> objCorners(4);
		objCorners[0] = cvPoint(0,0); 
		objCorners[1] = cvPoint( imgObject.cols, 0 );
		objCorners[2] = cvPoint( imgObject.cols, imgObject.rows ); 
		objCorners[3] = cvPoint( 0, imgObject.rows );
		vector<cv::Point2f> sceneCorners(4);
		try {
			perspectiveTransform( objCorners, sceneCorners, H);
		} catch(cv::Exception) {
			cout << "Can't transform" << endl;
			return cv::Point(-1, -1);
		}
		
		rotation = getRotationFromPoints(sceneCorners[0].x, sceneCorners[0].y, sceneCorners[1].x, sceneCorners[1].y);
		scaling = getScalingFromPoints(sceneCorners[0].x, sceneCorners[0].y, sceneCorners[1].x, sceneCorners[1].y, imgObject.cols);
		double angle1 = findAngle(sceneCorners[0].x, sceneCorners[0].y,
			                      sceneCorners[1].x, sceneCorners[1].y,
			                      sceneCorners[2].x, sceneCorners[2].y);
		double angle2 = findAngle(sceneCorners[1].x, sceneCorners[1].y,
			                      sceneCorners[2].x, sceneCorners[2].y,
			                      sceneCorners[3].x, sceneCorners[3].y);
		double angle3 = findAngle(sceneCorners[2].x, sceneCorners[2].y,
			                      sceneCorners[3].x, sceneCorners[3].y,
			                      sceneCorners[0].x, sceneCorners[0].y);
		double angle4 = findAngle(sceneCorners[3].x, sceneCorners[3].y,
			                      sceneCorners[0].x, sceneCorners[0].y,
			                      sceneCorners[1].x, sceneCorners[1].y);
		if (abs(angle1 - M_PI / 2) > maxAngleTolerance) {
			cout << "Angle tolerance" << endl
			     << "Angle: " << abs(angle1 - M_PI / 2) << endl;
			return cv::Point(-1, -1);
		}
		if (abs(angle2 - M_PI / 2) > maxAngleTolerance) {
			cout << "Angle tolerance" << endl
			     << "Angle: " << abs(angle2 - M_PI / 2) << endl;
			return cv::Point(-1, -1);
		}
		if (abs(angle3 - M_PI / 2) > maxAngleTolerance) {
			cout << "Angle tolerance" << endl
			     << "Angle: " << abs(angle3 - M_PI / 2) << endl;
			return cv::Point(-1, -1);
		}
		if (abs(angle4 - M_PI / 2) > maxAngleTolerance) {
			cout << "Angle tolerance" << endl
			     << "Angle: " << abs(angle4 - M_PI / 2) << endl;
			return cv::Point(-1, -1);
		}
		if (abs(1 - scaling) > maxScaling) {
			cout << "Scaling tolerance" << endl;
			return cv::Point(-1, -1);
		}
		if (abs(rotation) > maxAngleTolerance) {
			cout << "Angle tolerance" << endl
			     << "Angle: " << abs(rotation) << endl;
			return cv::Point(-1, -1);
		}
		topLeft = sceneCorners[0];
		return sceneCorners[0];
	}

	SurfTemplate::~SurfTemplate() {
	}

#endif