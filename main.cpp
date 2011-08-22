#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>
#include "Contour.h"
#include "ContoursDetector.h"

using namespace cv;

//void thresh_callback(int, void* );


int main()
{
	Contour kontury;
	ContoursDetector detector("D:/kart.PNG",kontury);
	namedWindow("canny",1);
	detector.setCannyParams(true,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
	detector.findContoursCanny();//problem function with parameters and then in callback without
	detector.showCannyEffect("canny","canny effect");
	cout<<detector.getObjectContours()->contours()->size();
	/*moments test
	detector.calculateContoursMoments();
	for(vector<Moments>::iterator it=detector.getObjectContours()->contoursMoments()->begin();
		it<detector.getObjectContours()->contoursMoments()->end();it++)
	{
		cout<<(*it).m00;
	}*/
	//mass centers test
	detector.calculateContoursMoments();
	detector.calculateMassCenters();
	cout<<detector.getObjectContours()->massCenters()->size();
	detector.showCannyEffect("canny","cannyEffect");
	
	waitKey(0);
	
	return 0;
}

