#ifndef erodefilter_h
#define erodefilter_h
	#include "Filter.h"

	using namespace std;

	class ErodeFilter : public Filter {
		private:
		protected:
		public:
			ErodeFilter();
			virtual ~ErodeFilter();
			cv::Mat apply(cv::Mat in);
			int kernelSize;
			int erosionType;
			string mode;
	};
#endif