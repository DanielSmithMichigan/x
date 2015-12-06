#ifndef Dialog_h
#define Dialog_h
	#include "DropButton.h"
	#include "OcrObject.h"
	#include "Scene.h"
	class Dialog {
		private:
			Scene* scene;
			int marginTop;
			int marginCell;
			int cellHeight;
			vector<OcrObject*> dialogBoxes;
		public:
			Dialog();
			bool select(string matchString);
			bool match(string matchString);
			void initialize();
	};
#endif