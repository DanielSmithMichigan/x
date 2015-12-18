#ifndef Map_cpp
#define Map_cpp
	#include "Map.h"

	Map::Map() {
	}

	void Map::initialize() {
		vector<plane>().swap(planes);
		struct plane minersGuild("MINERS_GUILD", "../images/MinersGuild.png");
		planes.push_back(minersGuild);
		struct plane falador("FALADOR", "../images/Falador.png");
		planes.push_back(falador);
		struct location miningGuild1;
		miningGuild1.x = 164;
		miningGuild1.y = 84;
		miningGuild1.plane = "MINERS_GUILD";
		locations["MINING_GUILD_1"] = miningGuild1;
		struct location minersGuildLadder;
		minersGuildLadder.x = 64;
		minersGuildLadder.y = 75;
		minersGuildLadder.plane = "MINERS_GUILD";
		locations["MINING_GUILD_LADDER"] = minersGuildLadder;
		struct location faladorLadder;
		faladorLadder.x = 96;
		faladorLadder.y = 90;
		faladorLadder.plane = "FALADOR";
		locations["FALADOR_LADDER"] = faladorLadder;
		struct location faladorBank;
		faladorBank.x = 73;
		faladorBank.y = 64;
		faladorBank.plane = "FALADOR";
		locations["FALADOR_BANK"] = faladorBank;

		width = 103;
		height = 103;

	    unique_ptr<ImageObject> worldMap (new ImageObject("../images/WorldMap.png"));
	    if (worldMap->initialize()) {
	    	cout << "Found using world map" << endl;
	        topLeft = cv::Point(worldMap->topLeft.x - 118, worldMap->topLeft.y - 118);
	    } else {
	    	cout << "Could not initialize using world map" << endl;
	        unique_ptr<ImageObject> helpButton (new ImageObject("../images/HelpButton.png"));
	        if (helpButton->initialize()) {
	            topLeft = cv::Point(worldMap->topLeft.x - 118, worldMap->topLeft.y + 32);
	        } else {
	            string error = "Could not locate map";
	            cout << error << endl;
	            throw(error);
	        }
	    }
	    Object::initialize();
	}

	bool Map::locate() {
		cout << "Attempting to find plane" << endl;
		unique_ptr<SurfTemplate> currentMap(new SurfTemplate(getImage()));
		for(vector<plane>::iterator iter = planes.begin(); iter != planes.end(); ++iter) {
			if (currentMap->match((*iter).image)) {
				currentPlane = (*iter).name;
				x = currentMap->topLeft.x + (width / 2);
				y = currentMap->topLeft.y + (height / 2);
				cout << "Plane is: " << (*iter).name << endl;
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
		int clickX = topLeft.x + (width / 2);
		int clickY = topLeft.y + (height/ 2);
		clickX += directionX == "EAST"? distanceX : -1 * distanceX;
		clickY += directionY == "SOUTH"? distanceY : -1 * distanceY;
		glideToPosition(clickX, clickY);
	}

	void Map::goTo(string l) {
		if (!locations.count(l)) {
			string error = "Could not find location: " + l;
			cout << error << endl;
			throw(error);
		}
		location loc = locations[l];
		while(distanceBetween(x, y, loc.x, loc.y) > 10) {
			approachPosition(l);
			cv::waitKey(500);
		}
	}

#endif