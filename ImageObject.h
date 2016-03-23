#ifndef ImageObject_h
#define ImageObject_h
	#include "Object.h"
	#include "Scene.h"
	#include "Template.h"
	#define MATCH_RGB 0
	#define MATCH_THRESHOLD 1

	using namespace std;

	class ImageObject : public Object {
		private:
			vector<unique_ptr<Template>> templates;
		public:
			ImageObject();
			ImageObject(string imageLocation);
			virtual ~ImageObject();
			void addTemplate(unique_ptr<Template> tmpl);
			bool initialize();
			bool match();
			bool waitForMatch(int numRetries = 20);
			int matchType;
	};
#endif