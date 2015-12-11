#ifndef Dialog_h
#define Dialog_h
	#include "OcrObject.h"
	#include "ImageObject.h"
	#include "Scene.h"

	class Dialog {
		private:
			unique_ptr<Scene> scene;
			int marginTop;
			int marginCell;
			int cellHeight;
			vector<unique_ptr<OcrObject>> dialogBoxes;
		public:
			Dialog();
			~Dialog();
			bool select(string matchString);
			bool match(string matchString);
			void initialize();
	};
#endif