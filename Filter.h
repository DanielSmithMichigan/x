#ifndef filter_h
#define filter_h
	#include "Scene.h"

	using namespace std;

	class Filter {
		private:
		protected:
		public:
			Filter();
			virtual ~Filter();
			virtual cv::Mat apply(cv::Mat in) = 0;
	};
#endif