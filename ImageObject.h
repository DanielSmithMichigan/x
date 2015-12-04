#ifndef ImageObject_h
#define ImageObject_h
	#include "Object.h"
	#include "Scene.h"
	#include "ImageTemplate.h"
	#define MATCH_RGB 0
	#define MATCH_THRESHOLD 1

	using namespace std;

	class ImageObject : public Object {
		private:
			vector<Template*> templates;
		public:
			ImageObject();
			ImageObject(string imageLocation);
			void addTemplate(Template* tmpl);
			void initialize();
			void match();
			int matchType;
	};
#endif