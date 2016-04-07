#ifndef Map_h
#define Map_h
	#include "ImageObject.h"
	#include "SurfTemplate.h"
	#include "MapButton.h"
	#define MAP_WIDTH 103
	#define MAP_HEIGHT 103
	#define MAP_COORD_OFFSET 0

	using namespace std;

	struct plane {
		cv::Mat image;
		string name;
		plane(string n, string loc) : name(n) {
			image = cv::imread(loc);
		}
	};

	struct location {
		string plane;
		int x;
		int y;
		map<string, bool> flags;
	};

	class Map : public Object {
		private:
			vector<plane> planes;
			map<string, location> locations;
			void approachPosition(string l);
			unique_ptr<MapButton> mapButton;
		public:
			Map();
			virtual ~Map();
			void waitDuringMovement(int maxRetries = 20);
			bool initialize();
			bool locate();
			bool goTo(string l, int maxDistance = 25);
			map<string, bool> getFlags(string location);
			string currentPlane;
			int x;
			int y;
	};
#endif