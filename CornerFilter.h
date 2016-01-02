#ifndef cornerfilter_h
#define cornerfilter_h
	#include "Filter.h"

	using namespace std;

	class CornerFilter : public Filter {
		private:
		protected:
		public:
			CornerFilter();
			virtual ~CornerFilter();
			cv::Mat apply(cv::Mat in);
			int cornerThreshold;
			int blockSize;
			int aperture;
			double k;
	};
#endif