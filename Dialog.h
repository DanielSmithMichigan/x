#ifndef Dialog_h
#define Dialog_h
	#include "DropButton.h"
	#include "OcrObject.h"
	class Dialog {
		private:
			int marginTop;
			int marginCell;
			int cellHeight;
			vector<OcrObject*> dialogBoxes;
		public:
			Dialog();
			void select(string matchString);
			void initialize();
	};
#endif