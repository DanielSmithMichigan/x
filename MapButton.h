#ifndef MapButton_h
#define MapButton_h
	#include "ImageObject.h"

	using namespace std;

	class MapButton : public Object {
		private:
		public:
			MapButton();
			virtual ~MapButton();
			bool initialize();
	};
#endif