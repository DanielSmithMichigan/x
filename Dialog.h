#ifndef Dialog_h
#define Dialog_h
	#include "DropButton.h"
	#include "OcrObject.h"
	class Dialog {
		private:
			int marginTop;
			int marginCell;
			int cellHeight;
		public:
			Dialog();
			void initialize();
	};
#endif