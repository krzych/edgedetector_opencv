#include "Contour.h"


Contour::Contour(void)
{
}


Contour::~Contour(void)
{
}

vector<vector<Point>>* Contour::contours()
{
	return &m_contours;
}

vector<Vec4i>* Contour::hierarchy()
{
	return &m_hierarchy;
}