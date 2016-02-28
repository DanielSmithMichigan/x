#ifndef windowfilter_h
#define windowfilter_h
	#include "Filter.h"
	#include "ImageObject.h"

	using namespace std;

	class WindowFilter : public Filter {
		private:
			cv::Point topLeft;
		protected:
		public:
			WindowFilter();
			virtual ~WindowFilter();
			cv::Mat apply(cv::Mat in);
	};
#endif