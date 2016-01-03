#ifndef Select_cpp
#define Select_cpp
	#include "Select.h"

	Select::Select(int minWaitTime, int minGuessDistance) 
	:  minGuessDistance(minGuessDistance), 
	   minWaitTime(minWaitTime) {
		dialog.reset(new Dialog());
		mapButton.reset(new MapButton());
	}

	Select::~Select() {

	}

	void Select::initialize() {
		mapButton->initialize();
		playerLocation.x = mapButton->topLeft.x - 442;
		playerLocation.y = mapButton->topLeft.y + 263;
	}

	bool Select::selectDialog(cv::Mat selectableImage, vector<string> goodDialog, vector<string> badDialog) {
        cv::Point closestLocation;
        bool found = false;
        double minDistance = -1;
        double currDistance = -1;

        while(true) {
        	found = false;
        	minDistance = -1;
			for( int x = 0; x < selectableImage.cols ; x++ )
			{ 
				for( int y = 0; y < selectableImage.rows; y++ )
				{
					if(selectableImage.at<uchar>(y,x) == 255)
					{
						currDistance = distanceTo(x, y, playerLocation.x, playerLocation.y);
						if (minDistance == -1 || currDistance < minDistance) {
							minDistance = currDistance;
							closestLocation = cv::Point(x, y);
							found = true;
						}
					}
				}
			}

            if (found) {
                glideToPosition(closestLocation.x, closestLocation.y, 4);
                click(RIGHT_CLICK);
                dialog->initialize();
				for(vector<string>::iterator iter = badDialog.begin(); iter != badDialog.end(); ++iter) {
					if (dialog->match(*iter)){
						dialog->select("Cancel");
                		cv::circle(selectableImage, closestLocation, minGuessDistance, CV_RGB(0,0,0), -1);
						continue;
					}
				}
				for(vector<string>::iterator iter = goodDialog.begin(); iter != goodDialog.end(); ++iter) {
					if (dialog->match(*iter)){
						dialog->select(*iter);
						nsleep(minWaitTime);
						return true;
					}
				}
				dialog->select("Cancel");
            } else {
                break;
            }
        }
        return false;
	}

#endif