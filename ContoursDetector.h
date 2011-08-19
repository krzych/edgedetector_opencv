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
	//canny params
	int m_cannyLowerThresh;
	int m_cannyHigherThresh;
	static const int m_maxCannyThresh =255;
	int m_cannyApertureSize; 
	bool m_cannyL2Gradient;
	int m_contoursMode; //openCV->findcontours, default CV_RETR_TREE
	int m_contoursMethod; //openCV->findcontours, default CV_CHAIN_APPROX_NONE

	string m_detectorWindowName; //detector window filename for showing results, convinient here because of trackbars params
	string m_effectWindowName;
	string m_imageFilename;
public:
	ContoursDetector(void);
	ContoursDetector(Mat& img, Contour& objContours);
	ContoursDetector(const string& imgFilename, Contour& objContours);
	~ContoursDetector(void);

	static void trackbarCallback(int param1, void* lpvoid ); 
	void setCannyParams(bool cannyL2Gradient, int contoursMode, int contoursMethod,int lowerThresh=100,int higherThresh=200, 
						int apertureSize=3);
	void findContoursCanny(); //find contours with Canny
																	 //parameters description openCV->findContours
																	 //deafult only external contours, no chain approximations
	void showCannyEffect(const string& windowName,const string& effectWindow);
	void showUpdate(const string& windowName);
};

