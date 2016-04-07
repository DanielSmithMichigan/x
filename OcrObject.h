#ifndef ocrobject_h
#define ocrobject_h
	#include "Object.h"
	
	using namespace std;

	class OcrObject : public Object {
		private:
			cv::Ptr<cv::text::OCRTesseract> ocr;
			int maxValue;
			int thresholdType;
			int minHeight;
			cv::Mat prepareImage(cv::Mat &imageIn);
		public:
			OcrObject();
			virtual ~OcrObject();
			bool initialize();
			bool match(string matchString);
			int threshold;
			string bestGuess;
	};
#endif