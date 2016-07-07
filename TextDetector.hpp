#ifndef BKRUKOWSKI_ODYN_TEXT_DETECTOR_H
#define BKRUKOWSKI_ODYN_TEXT_DETECTOR_H

#include "opencv2/opencv.hpp"

namespace Odyn
{
	class TextDetector
	{
		private:
			tesseract::TessBaseAPI *api;

		public:
			TextDetector(tesseract::TessBaseAPI *api, cv::Mat *image);
			std::string detectText(cv::Rect rect);
	};	
}

Odyn::TextDetector::TextDetector(tesseract::TessBaseAPI *api, cv::Mat *image) {
	this->api = api;
	api->SetImage(
		(uchar*) image->data,
		image->size().width,
		image->size().height,
		image->channels(),
		image->step1()
	);
}

std::string Odyn::TextDetector::detectText(cv::Rect rect) {
	this->api->SetRectangle(
		rect.x,
		rect.y,
		rect.width,
		rect.height
	);

    return api->GetUTF8Text();
}

#endif