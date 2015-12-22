#ifndef rangefilter_h
#define rangefilter_h
	#include "Filter.h"

	using namespace std;

	class RangeFilter : public Filter {
		private:
		protected:
		public:
			RangeFilter();
			virtual ~RangeFilter();
			cv::Mat apply(cv::Mat in);
			int lowHue;
			int highHue;
			int lowSaturation;
			int highSaturation;
			int lowValue;
			int highValue;
	};
#endif