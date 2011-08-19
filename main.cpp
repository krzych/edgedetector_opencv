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
	ContoursDetector detector("D:/abckompressed.JPG",kontury);
	namedWindow("canny",1);
	detector.findContoursCanny();
	detector.showCannyEffect("canny","canny effect");
	waitKey(0);
	
	return 0;
}

/*void thresh_callback(int, void* )
{
  Mat canny_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  /// Detect edges using canny
  Canny( imageGray, canny_output, lowerThresh, higherThresh, 3 );
  /// Find contours
  findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  /// Draw contours
  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
  for( int i = 0; i< contours.size(); i++ )
     {
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
     }

  /// Show in a window
  namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
  imshow( "Contours", drawing );
}*/