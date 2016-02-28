#ifndef Map_cpp
#define Map_cpp
	#include "Map.h"

	Map::Map() {
		vector<plane>().swap(planes);
		struct plane minersGuild("MINERS_GUILD", "../images/MinersGuild.png");
		planes.push_back(minersGuild);
		struct plane falador("FALADOR", "../images/Falador.png");
		planes.push_back(falador);
		struct plane morytania("MORYTANIA", "../images/Morytania.png");
		planes.push_back(morytania);
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

		struct location morytania1;
		morytania1.x = 120;
		morytania1.y = 108;
		morytania1.plane = "MORYTANIA";
		locations["MORYTANIA_1"] = morytania1;

		struct location morytania2;
		morytania2.x = 130;
		morytania2.y = 108;
		morytania2.plane = "MORYTANIA";
		locations["MORYTANIA_2"] = morytania2;

		struct location morytania3;
		morytania3.x = 120;
		morytania3.y = 118;
		morytania3.plane = "MORYTANIA";
		locations["MORYTANIA_3"] = morytania3;


		width = 103;
		height = 103;

		mapButton.reset(new MapButton());
		mapButton->initialize();
		topLeft = cv::Point(mapButton->topLeft.x - 118, mapButton->topLeft.y - 118);
	}

	Map::~Map() {

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

	map<string, bool> Map::getFlags(string location) {
		if (!locations.count(location)) {
			string error = "Could not find location: " + location;
			cout << error << endl;
			throw(error);
		}
		return locations[location].flags;
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