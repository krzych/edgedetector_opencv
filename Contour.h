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
public:
	Contour(void);
	~Contour(void);
	vector<vector<Point>>* contours();
	vector<Vec4i>* hierarchy();
};

