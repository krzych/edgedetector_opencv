#pragma once

#include <opencv2\opencv.hpp>
#include "Contour.h"

using namespace cv;

class ContoursDetector
{
private:
	Contour* m_objectContours;
	Mat m_image; //image to find contours
	Mat m_imageGray; //gray image
	Mat m_cannyOutput; //output image from Canny
	int m_cannyLowerThresh;
	int m_cannyHigherThresh;
	static const int m_maxCannyThresh =255;

	string m_detectorWindowName; //detector window filename for showing results, convinient here because of trackbars params
	string m_effectWindowName;
	string m_imageFilename;
public:
	ContoursDetector(void);
	ContoursDetector(Mat& img, Contour& objContours);
	ContoursDetector(const string& imgFilename, Contour& objContours);
	~ContoursDetector(void);

	static void trackbarCallback(int param1, void* lpvoid ); 
	void findContoursCanny(int apertureSize=3,bool L2Gradient=false,
		int mode=CV_RETR_EXTERNAL, int method=CV_CHAIN_APPROX_NONE); //find contours with Canny
																	 //parameters description openCV->findContours
																	 //deafult only external contours, no chain approximations
	void showCannyEffect(const string& windowName,const string& effectWindow);
	void showUpdate(const string& windowName);
};

