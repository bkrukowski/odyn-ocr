#ifndef BKRUKOWSKI_ODYN_DEFAULT_TESSERACT_H
#define BKRUKOWSKI_ODYN_DEFAULT_TESSERACT_H

#include "opencv2/opencv.hpp"
#include <tesseract/baseapi.h>

namespace Odyn
{
	class DefaultTesseract
	{
		public:
			tesseract::TessBaseAPI *createDefaultTesseract();
	};
}

tesseract::TessBaseAPI *Odyn::DefaultTesseract::createDefaultTesseract() {
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    if (api->Init(NULL, "eng")) {
        throw "Could not initialize tesseract!";
    }
    api->SetVariable("language_model_penalty_non_freq_dict_word", "1");
    api->SetVariable("language_model_penalty_non_dict_word ", "1");
    api->SetVariable("load_system_dawg", "0");
    api->SetVariable("tessedit_char_whitelist", "abcdefghijklmnopqrstuvwxyz0123456789");

    return api;
}

#endif