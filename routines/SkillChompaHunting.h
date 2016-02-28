#ifndef skillchompahunting_h
#define skillchompahunting_h
	#include "../Inventory.h"
	#include "../Map.h"
	#include "../objects/BoxTrap.h"
	#include "../Dialog.h"
	#include "../ImageObject.h"

	using namespace std;

	class SkillChompaHunting {
		private:
		    unique_ptr<Inventory> inventory;
		    unique_ptr<Map> interfaceMap;
		    unique_ptr<BoxTrap> boxTrap;
		    unique_ptr<Dialog> dialog;
		    unique_ptr<ImageObject> hunterIcon;
		    unique_ptr<Scene> scene;
		    queue<cv::Point> huntingLocations;
		protected:
		public:
			SkillChompaHunting();
			virtual ~SkillChompaHunting();
			void run();
			bool gotoNextLocation();
			cv::Point getNextLocation();
	};
#endif