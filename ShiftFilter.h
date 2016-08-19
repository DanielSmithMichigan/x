#ifndef ShiftFilter_h
#define ShiftFilter_h
	#include "Filter.h"

	using namespace std;

	class ShiftFilter : public Filter {
		private:
		protected:
		public:
			ShiftFilter();
			virtual ~ShiftFilter();
			cv::Mat apply(cv::Mat in);
			int offsetX;
			int offsetY;
	};
#endif