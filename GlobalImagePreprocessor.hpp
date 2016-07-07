#ifndef BKRUKOWSKI_ODYN_GLOBAL_IMAGE_PREPROCESSOR_H
#define BKRUKOWSKI_ODYN_GLOBAL_IMAGE_PREPROCESSOR_H

#include "opencv2/opencv.hpp"
#include "all.hpp"

namespace Odyn
{
	class GlobalImagePreprocessor
	{
		public:
			cv::Mat preprocessImage(cv::Mat image);
	};
}

cv::Mat Odyn::GlobalImagePreprocessor::preprocessImage(cv::Mat image) {
	ODYN_DEBUG("preprocessImage");
    cv::Mat result;
    image.copyTo(result);
    result.convertTo(result, -1, 1.3, 0);
    return result;
}

#endif