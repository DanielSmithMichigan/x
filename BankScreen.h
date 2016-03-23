#ifndef BankScreen_h
#define BankScreen_h
	#include "ImageObject.h"
	#include "Scene.h"

	class BankScreen {
		private:
			unique_ptr<Scene> scene;
		public:
			BankScreen();
			~BankScreen();
			bool close();
			void storeAll();
			void loadPresetOne();
			bool open();
	};
#endif