#ifndef agility_cpp
#define agility_cpp
	#include "Agility.h"
	#define ZOOM_IN_KEY 65369
	#define ZOOM_OUT_KEY 65397
	#define VIEW_UP_KEY 65391
	#define VIEW_DOWN_KEY 65396
	#define ONE_KEY 65546
	#define TWO_KEY 65547

	Agility::Agility() {
		mapButton.reset(new MapButton());
		mapButton->rs3=true;
		scene.reset(new Scene());
		dialog.reset(new Dialog());
		minActionTime = 49;
		maxActionTime = 81;
		minButtonTime = 9;
		maxButtonTime = 17;
		maxMovement = 20;
	}

	Agility::~Agility() {

	}

	void Agility::run() {
		scene->redraw();
		mapButton->initialize();
		unique_ptr<Object> clickSpot(new Object());
		clickSpot->width = 7;
		clickSpot->height = 11;
		clickSpot->topLeft = cv::Point(mapButton->topLeft.x - 500, mapButton->topLeft.y + 283);
		clickSpot->initialize();
		unique_ptr<Object> compass(new Object());
		compass->width = 19;
		compass->height = 19;
		compass->topLeft = cv::Point(mapButton->topLeft.x - 145, mapButton->topLeft.y - 148);
		compass->initialize();
		compass->clickOn(RIGHT_CLICK);
		dialog->initialize();
		dialog->select("FaceSouth");
		vector<int> randVect;
		randVect.push_back(1);
		randVect.push_back(2);
		randVect.push_back(3);
		keypress(VIEW_DOWN_KEY, 500);
		int max = 100;
		while(true) {
			nsleep(randomBetween(3000, 5000));
			for (int i = 0; i < max; i++) {
				for (auto it = begin (randVect); it != end (randVect); ++it) {
					if (*it == 1) {
						keypress(ONE_KEY, randomBetween(minButtonTime, maxButtonTime));
					}
					if (*it == 2) {
						keypress(TWO_KEY, randomBetween(minButtonTime, maxButtonTime));
					}
					if (*it == 3) {
						clickSpot->clickOn();
					}
					nsleep(randomBetween(minActionTime, maxActionTime));
				}
				if (chance(10)) {
					cout << "SHUFFLING" << endl;
  					random_shuffle ( randVect.begin(), randVect.end() );
				}
				if (chance(10)) {
					cout << "MOVING RIGHT" << endl;
					clickSpot->topLeft.x += 2;
				} else if (chance(10)) {
					cout << "MOVING LEFT" << endl;
					clickSpot->topLeft.x -= 2;
				}
				if (clickSpot->topLeft.x < mapButton->topLeft.x - 500 - maxMovement) {
					clickSpot->topLeft.x = mapButton->topLeft.x - 500 - maxMovement;
				}
				if (clickSpot->topLeft.x > mapButton->topLeft.x - 500 + maxMovement) {
					clickSpot->topLeft.x = mapButton->topLeft.x - 500 + maxMovement;
				}
				cout << "i: " << i << " / " << max << endl;
			}
			max = randomBetween(81, 192);
		}
	}

#endif