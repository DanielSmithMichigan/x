#ifndef surftemplate_cpp
#define surftemplate_cpp
	#include "SurfTemplate.h"
	// using namespace cv;
	// using namespace cv::xfeatures2d;

	SurfTemplate::SurfTemplate(cv::Mat imgObj) : ImageTemplate(imgObj) {
		distance = .15;
		minHessian = 4;
		surf = cv::xfeatures2d::SURF::create(minHessian);
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
		cout << "SIZE: " << goodMatches.size() << endl;
		cv::Mat H;
		try {
			H = cv::findHomography( objPoints, scenePoints, CV_RANSAC );
		} catch(cv::Exception) {
			return cv::Point(-1, -1);
		}

		cout << "CONTINUING" << endl;

		vector<cv::Point2f> objCorners(4);
		objCorners[0] = cvPoint(0,0); 
		objCorners[1] = cvPoint( imgObject.cols, 0 );
		objCorners[2] = cvPoint( imgObject.cols, imgObject.rows ); 
		objCorners[3] = cvPoint( 0, imgObject.rows );
		vector<cv::Point2f> sceneCorners(4);

		perspectiveTransform( objCorners, sceneCorners, H);
		cv::Mat imgMatches;
		drawMatches( imgObject, keypointsObject, imgScene, keypointsScene,
			goodMatches, imgMatches, cv::Scalar::all(-1), cv::Scalar::all(-1),
			vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
		cout << sceneCorners[0] << endl;
		cout << sceneCorners[1] << endl;
		cout << sceneCorners[2] << endl;
		cout << sceneCorners[3] << endl;
		cv::line( imgMatches, sceneCorners[0] + cv::Point2f( imgObject.cols, 0), sceneCorners[1] + cv::Point2f( imgObject.cols, 0), cv::Scalar(0, 255, 0), 4 );
		cv::line( imgMatches, sceneCorners[1] + cv::Point2f( imgObject.cols, 0), sceneCorners[2] + cv::Point2f( imgObject.cols, 0), cv::Scalar( 0, 255, 0), 4 );
		cv::line( imgMatches, sceneCorners[2] + cv::Point2f( imgObject.cols, 0), sceneCorners[3] + cv::Point2f( imgObject.cols, 0), cv::Scalar( 0, 255, 0), 4 );
		cv::line( imgMatches, sceneCorners[3] + cv::Point2f( imgObject.cols, 0), sceneCorners[0] + cv::Point2f( imgObject.cols, 0), cv::Scalar( 0, 255, 0), 4 );
		imshow("W", imgMatches);
		cv::waitKey();
		return sceneCorners[0];
	}

	SurfTemplate::~SurfTemplate() {
	}

#endif