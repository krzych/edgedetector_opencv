#pragma once

#include <vector>
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>

using namespace cv;

class Contour
{
private:
	vector<vector<Point>> m_contours; //vector of vectors of contours points
	vector<Vec4i> m_hierarchy; //hierarchy of contours, if they are inside etc.
	vector<Moments> m_moments; //contours moments, used for mass center calculations
	vector<Point2f> m_massCenters; //mass centers for each contour, used to calculate displacement of object
								   //only one contour seen or evaluated which contour is object contour
public:
	Contour(void);
	~Contour(void);
	vector<vector<Point>>* contours();
	vector<Vec4i>* hierarchy();
	vector<Moments>* contoursMoments();
	vector<Point2f>* massCenters();
};

