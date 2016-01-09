#ifndef skillchompahunting_h
#define skillchompahunting_h
	#include "../Inventory.h"
	#include "../Map.h"
	#include "../objects/BoxTrap.h"

	using namespace std;

	class SkillChompaHunting {
		private:
		    unique_ptr<Inventory> inventory;
		    unique_ptr<Map> interfaceMap;
		    unique_ptr<BoxTrap> boxTrap;
		protected:
		public:
			SkillChompaHunting();
			virtual ~SkillChompaHunting();
			void run();
	};
#endif