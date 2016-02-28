#ifndef agility_h
#define agility_h
	#include "../MapButton.h"
	#include "../Scene.h"
	#include "../Dialog.h"

	using namespace std;

	class Agility {
		private:
			unique_ptr<MapButton> mapButton;
			unique_ptr<Scene> scene;
			unique_ptr<Dialog> dialog;
			int minActionTime;
			int maxActionTime;
			int minButtonTime;
			int maxButtonTime;
			int maxMovement;
		protected:
		public:
			Agility();
			virtual ~Agility();
			void run();
	};
#endif