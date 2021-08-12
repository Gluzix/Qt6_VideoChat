#include "CameraPropertiesHolderWorker.h"

CameraPropertiesHolderWorker::CameraPropertiesHolderWorker(cv::VideoCapture* cap, QMutex* mutex, QObject* parent)
	: m_Cap(cap)
	, m_Mutex(mutex)
	, QObject(parent)
{

}
CameraPropertiesHolderWorker::~CameraPropertiesHolderWorker()
{

}

void CameraPropertiesHolderWorker::Process()
{
	QMutexLocker locker(m_Mutex);
	for (int i = 0; i < NUMBER_OF_CV_FEATURES; i++)
	{
		double value = m_Cap->get(i);
		if (value != 0)
		{
			std::string propertyName = CheckParameterByIndex(i);
			emit SendPropertyName(QString::fromStdString(propertyName));
		}
	}
}

std::string CameraPropertiesHolderWorker::CheckParameterByIndex(int index)
{
	std::string propertyName;
	switch (index)
	{
		case cv::CAP_PROP_FRAME_WIDTH: propertyName = "Frame Width";  break;
		case cv::CAP_PROP_FRAME_HEIGHT: propertyName = "Frame Height";  break;
		case cv::CAP_PROP_FPS: propertyName = "FPS";  break;
		case cv::CAP_PROP_FRAME_COUNT: propertyName = "Frame Count";  break;
		case cv::CAP_PROP_BRIGHTNESS: propertyName = "Brightness";  break;
		case cv::CAP_PROP_CONTRAST: propertyName = "Contrast";   break;
		case cv::CAP_PROP_SATURATION: propertyName = "Saturation";  break;
		case cv::CAP_PROP_HUE: propertyName = "Hue";  break;
		case cv::CAP_PROP_GAIN: propertyName = "Gain";  break;
		case cv::CAP_PROP_EXPOSURE: propertyName = "Exposure";   break;
		case cv::CAP_PROP_SHARPNESS: propertyName = "Sharpness";  break;
		case cv::CAP_PROP_GAMMA: propertyName = "Gamma";  break;
		default: propertyName = "<not-supported>"; break;
	}
	return propertyName;
}