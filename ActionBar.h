#ifndef ActionBar_h
#define ActionBar_h
	#include "ImageObject.h"
	#include "Scene.h"

	class ActionBar {
		private:
			unique_ptr<Scene> scene;
			string mode;
			map<string, unique_ptr<ImageObject>> buttonImages;
			vector<string> buttons;
		public:
			ActionBar();
			~ActionBar();
			bool initialize();
			bool select(string newMode);
	};
#endif