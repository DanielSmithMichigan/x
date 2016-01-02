#ifndef Map_cpp
#define Map_cpp
	#include "Map.h"

	Map::Map() {
		vector<plane>().swap(planes);
		struct plane minersGuild("MINERS_GUILD", "../images/MinersGuild.png");
		planes.push_back(minersGuild);
		struct plane falador("FALADOR", "../images/Falador.png");
		planes.push_back(falador);
		struct location miningGuild1;
		miningGuild1.x = 175;
		miningGuild1.y = 136;
		miningGuild1.plane = "MINERS_GUILD";
		locations["MINING_GUILD_1"] = miningGuild1;
		struct location minersGuildLadder;
		minersGuildLadder.x = 63;
		minersGuildLadder.y = 136;
		minersGuildLadder.plane = "MINERS_GUILD";
		locations["MINING_GUILD_LADDER"] = minersGuildLadder;
		struct location faladorLadder;
		faladorLadder.x = 128;
		faladorLadder.y = 181;
		faladorLadder.plane = "FALADOR";
		locations["FALADOR_LADDER"] = faladorLadder;
		struct location faladorBank;
		faladorBank.x = 100;
		faladorBank.y = 123;
		faladorBank.plane = "FALADOR";
		locations["FALADOR_BANK"] = faladorBank;

		width = 103;
		height = 103;

	    unique_ptr<ImageObject> worldMap (new ImageObject("../images/WorldMap.png"));
	    if (worldMap->initialize()) {
	        topLeft = cv::Point(worldMap->topLeft.x - 118, worldMap->topLeft.y - 118);
	    } else {
	        unique_ptr<ImageObject> helpButton (new ImageObject("../images/HelpButton.png"));
	        if (helpButton->initialize()) {
	            topLeft = cv::Point(worldMap->topLeft.x - 118, worldMap->topLeft.y + 32);
	        } else {
	            string error = "Could not locate map";
	            cout << error << endl;
	            throw(error);
	        }
	    }
	}

	void Map::initialize() {
	    Object::initialize();
		while(true) {
			if (locate()) {
				break;
			}
			nsleep(500);
		}
	}

	bool Map::locate() {
		unique_ptr<SurfTemplate> currentMap(new SurfTemplate(getImage()));
		for(vector<plane>::iterator iter = planes.begin(); iter != planes.end(); ++iter) {
			cout << "Testing: " << (*iter).name << endl;
			if (currentMap->match((*iter).image)) {
				currentPlane = (*iter).name;
				x = currentMap->topLeft.x + (width / 2);
				y = currentMap->topLeft.y + (height / 2);
				cout << "Plane is: " << (*iter).name 
				     << " X: " << x << " Y: " << y
					 << endl;
				return true;
			}
		}
		cout << "Could not find plane" << endl;
		return false;
	}

	void Map::approachPosition(string l) {
		if (!locations.count(l)) {
			string error = "Could not find location: " + l;
			cout << error << endl;
			throw(error);
		}
		location loc = locations[l];
		int maxDistance = width / 2;
		string directionX = x > loc.x? "WEST" : "EAST";
		string directionY = y > loc.y? "NORTH" : "SOUTH";
		int distanceX = min(abs(x - loc.x), maxDistance);
		int distanceY = min(abs(y - loc.y), maxDistance);
		int clickX = topLeft.x + (width / 2) + MAP_COORD_OFFSET;
		int clickY = topLeft.y + (height/ 2) + MAP_COORD_OFFSET;
		clickX += directionX == "EAST"? distanceX : -1 * distanceX;
		clickY += directionY == "SOUTH"? distanceY : -1 * distanceY;
		glideToPosition(clickX, clickY);
		click(LEFT_CLICK);
	}

	bool Map::goTo(string l, int maxDistance) {
		if (!locations.count(l)) {
			string error = "Could not find location: " + l;
			cout << error << endl;
			throw(error);
		}
		while (true) {
			if (locate()) {
				break;
			}
			nsleep(500);
		}
		location loc = locations[l];
	    while (loc.plane != currentPlane) {
	    	cout << "Current plane: " << currentPlane << endl
	    	     << "Target plane: " << loc.plane << endl;
	    	bool result = locate();
	        cout << "Locate result: " << result << endl;
	        nsleep(500);
	    }
	    double dist = distanceBetween(x, y, loc.x, loc.y);
	    cout << "Distance: " << dist << endl;
	    if (dist > maxDistance) {
			while(dist > maxDistance) {
				if (locate()) {
					approachPosition(l);
				}
				nsleep(1500);
			    dist = distanceBetween(x, y, loc.x, loc.y);
			    cout << "Distance: " << dist << endl;
			}
			nsleep(2500);
		}
		return true;
	}

#endif