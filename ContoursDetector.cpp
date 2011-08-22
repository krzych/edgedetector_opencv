#include "ContoursDetector.h"


ContoursDetector::ContoursDetector(void)
	:m_cannyLowerThresh(100),m_cannyHigherThresh(200),m_cannyApertureSize(3),m_cannyL2Gradient(false),
	m_contoursMode(CV_RETR_TREE),m_contoursMethod(CV_CHAIN_APPROX_NONE)
{
}

ContoursDetector::ContoursDetector(Mat& img, Contour& objContours)
	:m_cannyLowerThresh(100), m_cannyHigherThresh(200),m_image(img), m_objectContours(&objContours),
	m_cannyApertureSize(3),m_cannyL2Gradient(false),m_contoursMode(CV_RETR_TREE),m_contoursMethod(CV_CHAIN_APPROX_NONE)
{
}

ContoursDetector::ContoursDetector(const string& imgFilename, Contour& objContours)
	:m_cannyLowerThresh(100),m_cannyHigherThresh(200),m_imageFilename(imgFilename), m_objectContours(&objContours),
	m_cannyApertureSize(3),m_cannyL2Gradient(false),m_contoursMode(CV_RETR_TREE),m_contoursMethod(CV_CHAIN_APPROX_NONE)
{
	m_image=imread(m_imageFilename,1);
}

ContoursDetector::~ContoursDetector(void)
{
}

void ContoursDetector::trackbarCallback(int param1, void* lpvoid)
{
	reinterpret_cast<ContoursDetector*>(lpvoid)->findContoursCanny();
	reinterpret_cast<ContoursDetector*>(lpvoid)->showUpdate(reinterpret_cast<ContoursDetector*>(lpvoid)->m_effectWindowName);
}

void ContoursDetector::setCannyParams(bool cannyL2Gradient, int contoursMode, int contoursMethod,int lowerThresh,int higherThresh, 
						int apertureSize)
{
	m_cannyL2Gradient=cannyL2Gradient;
	m_contoursMode=contoursMode;
	m_contoursMethod=contoursMethod;
	m_cannyLowerThresh=lowerThresh;
	m_cannyHigherThresh=higherThresh;
	m_cannyApertureSize=apertureSize;
}

void ContoursDetector::findContoursCanny()
{
	cvtColor(m_image,m_imageGray,CV_BGR2GRAY);
	blur(m_imageGray,m_imageGray,Size(3,3));
	Canny(m_imageGray,m_cannyOutput,m_cannyLowerThresh,m_cannyHigherThresh,	m_cannyApertureSize,m_cannyL2Gradient);
	findContours(m_cannyOutput,*m_objectContours->contours(),*m_objectContours->hierarchy(),
		         m_contoursMode, m_contoursMethod, Point(0, 0) );
	//imshow("effect",m_cannyOutput);
	
}

void ContoursDetector::showCannyEffect(const string& windowName, const string& effectWindow)
{
	m_detectorWindowName=windowName;
	m_effectWindowName=effectWindow;
	imshow(m_detectorWindowName,m_image);
	createTrackbar("Lower canny threshold",m_detectorWindowName,&m_cannyLowerThresh,m_maxCannyThresh,trackbarCallback,this);
	createTrackbar("Higher canny treshold",m_detectorWindowName,&m_cannyHigherThresh,m_maxCannyThresh,trackbarCallback,this);
	imshow(effectWindow,m_cannyOutput);//effect
}

void ContoursDetector::showUpdate(const string& windowName)
{
	imshow(windowName,m_cannyOutput);
}

void ContoursDetector::calculateContoursMoments()
{
	/*for(int i=0; i<m_objectContours->contours()->size();i++)
	{
		Mat temp(m_objectContours->contours()->at(i),false);
		(m_objectContours->contours())->at(i);
		m_objectContours->contoursMoments()->at(i)=moments(temp,false);
	}*/
	for(vector<vector<Point>>::iterator i=m_objectContours->contours()->begin();i<m_objectContours->contours()->end();i++)
	{
		Mat temp(*i,false);
		m_objectContours->contoursMoments()->push_back(moments(temp,false));
	}
}

void ContoursDetector::calculateMassCenters()
{
	for(vector<Moments>::iterator i=m_objectContours->contoursMoments()->begin(); 
		i<m_objectContours->contoursMoments()->end();i++)
	{
		m_objectContours->massCenters()->push_back(Point2f(i->m10/i->m00 , i->m01/i->m00));
	}
	for(int i=0;i<m_objectContours->massCenters()->size();i++)
	{
		cout<<" "<<m_objectContours->massCenters()->at(i).x<<" "<<m_objectContours->massCenters()->at(i).y;

		circle(m_cannyOutput,m_objectContours->massCenters()->at(i),5,Scalar(255,255,255));
		imshow("abc",m_cannyOutput);
	}
}