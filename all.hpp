#ifndef BKRUKOWSKI_ODYN_ALL_HEADERS
#define BKRUKOWSKI_ODYN_ALL_HEADERS

#if defined(ODYN_DEBUGGER_ACTIVE) && ODYN_DEBUGGER_ACTIVE
	#define ODYN_DEBUG(info) std::cout << "ODYN " << __FILE__ << ":" << __LINE__ << " " << info << "\n"
#else
	#define ODYN_DEBUG(info)
#endif

#include "EdgeDetector.hpp"
#include "TextDetector.hpp"
#include "DefaultTesseract.hpp"
#include "OCRImagePreprocessor.hpp"
#include "GlobalImagePreprocessor.hpp"

namespace Odyn
{
	std::string detectText(std::string path) {
	    ODYN_DEBUG("start detect text");
	    Odyn::DefaultTesseract *defApiConstructor = new Odyn::DefaultTesseract;
	    tesseract::TessBaseAPI *api = defApiConstructor->createDefaultTesseract();
	    delete defApiConstructor;
	    
	    ODYN_DEBUG("reading image");
	    Odyn::GlobalImagePreprocessor *globalPreprocessor = new Odyn::GlobalImagePreprocessor();
	    cv::Mat input = globalPreprocessor->preprocessImage(cv::imread(path.c_str()));
	    delete globalPreprocessor;

	    Odyn::OCRImagePreprocessor *imgPreprocessor = new Odyn::OCRImagePreprocessor();
	    cv::Mat imgPreprocessed = imgPreprocessor->preprocessImage(input);
	    delete imgPreprocessor;

	    Odyn::EdgeDetector *detector = new Odyn::EdgeDetector();
	    std::vector<cv::Rect> rect = detector->detectEdges(input);
	    delete detector;

	    std::stringstream result;

	    Odyn::TextDetector *textDetector = new Odyn::TextDetector(api, &imgPreprocessed);
	    ODYN_DEBUG("before rect loop");
	    for (int i=0; i< rect.size(); i++) {
	        ODYN_DEBUG("detecting text");
	        textDetector->detectText(rect[i]);
	        result << api->GetUTF8Text();
	    }
	    delete textDetector;

	    api->End();

	    return result.str();
	}
}

#endif