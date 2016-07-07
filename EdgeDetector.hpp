#ifndef BKRUKOWSKI_ODYN_EDGE_DETECTOR_H
#define BKRUKOWSKI_ODYN_EDGE_DETECTOR_H

#include <vector>
#include "opencv2/opencv.hpp"
#include "all.hpp"

namespace Odyn
{
	class EdgeDetector
	{
		public:
			std::vector<cv::Rect> detectEdges(cv::Mat image);
	};	
}

std::vector<cv::Rect> Odyn::EdgeDetector::detectEdges(cv::Mat img) {
	ODYN_DEBUG("start detectEdges");
    std::vector<cv::Rect> boundRect;
    cv::Mat img_gray, img_sobel, img_threshold, element;
    cvtColor(img, img_gray, CV_BGR2GRAY);
    cv::Sobel(img_gray, img_sobel, CV_8U, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);
    cv::GaussianBlur(img_sobel, img_sobel, cv::Size(0, 0), 3);

    int erosion_type = cv::MORPH_ELLIPSE;
    float erosion_size = 2;
    element = getStructuringElement(
    	erosion_type,
    	cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
    	cv::Point(erosion_size, erosion_size)
    );
    ODYN_DEBUG("dilate");
    dilate(img_sobel, img_sobel, element);

	ODYN_DEBUG("threshold");
    cv::threshold(img_sobel, img_threshold, 0, 1000, CV_THRESH_OTSU + CV_THRESH_BINARY);
    element = getStructuringElement(cv::MORPH_RECT, cv::Size(17, 3) );
    ODYN_DEBUG("morphologyEx");
    cv::morphologyEx(img_threshold, img_threshold, CV_MOP_CLOSE, element);
    cv::Mat img_erode;
    std::vector< std::vector<cv::Point> > contours;
    ODYN_DEBUG("findContours");
    cv::findContours(img_threshold, contours, 0, 1);
    ODYN_DEBUG("after findContours");
    std::vector<std::vector<cv::Point> > contours_poly( contours.size() );
    for( int i = 0; i < contours.size(); i++ ) {
        if (contours[i].size()>100)
        {
        	ODYN_DEBUG("approxPolyDP");
            cv::approxPolyDP( cv::Mat(contours[i]), contours_poly[i], 3, true );
            cv::Rect appRect( boundingRect( cv::Mat(contours_poly[i]) ));
            if (appRect.width>appRect.height)
                boundRect.push_back(appRect);
        }
    }
    ODYN_DEBUG("stop detectEdges");
    return boundRect;
}

#endif