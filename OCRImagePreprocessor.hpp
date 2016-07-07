#ifndef BKRUKOWSKI_ODYN_OCR_IMAGE_PREPROCESSOR_H
#define BKRUKOWSKI_ODYN_OCR_IMAGE_PREPROCESSOR_H

#include "opencv2/opencv.hpp"
#include "all.hpp"

namespace Odyn
{
	class OCRImagePreprocessor
	{
		public:
			cv::Mat preprocessImage(cv::Mat image);
	};
}

cv::Mat Odyn::OCRImagePreprocessor::preprocessImage(cv::Mat image) {
	ODYN_DEBUG("start PreprocessImage");
    cv::Mat result;
    image.copyTo(result);
    int erosion_type = cv::MORPH_ELLIPSE;
    float erosion_size = 2;
    cv::Mat element = getStructuringElement(
    	erosion_type,
    	cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
    	cv::Point(erosion_size, erosion_size)
    );
    ODYN_DEBUG("erode");
    erode( result, result, element );
    erosion_size = 2.5;
    element = getStructuringElement(
    	erosion_type,
    	cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
    	cv::Point(erosion_size, erosion_size)
    );
    ODYN_DEBUG("dilate");
    dilate( result, result, element );
    ODYN_DEBUG("blur");
    cv::GaussianBlur(image, result, cv::Size(0, 0), 3);
    ODYN_DEBUG("addWeighted");
    cv::addWeighted(image, 1.2, result, -0.5, 0, result);
    ODYN_DEBUG("stop PreprocessImage");
    return result;
}

#endif