#ifndef Map_h
#define Map_h
	#include "ImageObject.h"
	#define MAP_WIDTH 103
	#define MAP_HEIGHT 103

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
	};

	class Map : public Object {
		private:
			vector<plane> planes;
			map<string, location> locations;
		public:
			Map();
			void initialize();
			bool locate();
			void goTo(string l);
			string currentPlane;
			int x;
			int y;
	};
#endif