#pragma once

#include <QObject>
#include <QWidget>
#include <QMutex>
#include <opencv2/videoio.hpp>
#include <opencv2/core.hpp>
#include "ui_CameraPropertiesHolder.h"

class Property
{
public:
	Property(int index)
	{
		CheckParameterByIndex(index);
	}

	~Property()
	{

	}

	std::string GetPropertyName()
	{
		return property_name;
	}

private:
	void CheckParameterByIndex(int index)
	{
		switch (index)
		{
			case cv::CAP_PROP_FRAME_WIDTH: property_name = "Frame Width";  break;
			case cv::CAP_PROP_FRAME_HEIGHT: property_name = "Frame Height";  break;
			case cv::CAP_PROP_FPS: property_name = "FPS";  break;
			case cv::CAP_PROP_FRAME_COUNT: property_name = "Frame Count";  break;
			case cv::CAP_PROP_BRIGHTNESS: property_name = "Brightness";  break;
			case cv::CAP_PROP_CONTRAST: property_name = "Contrast";   break;
			case cv::CAP_PROP_SATURATION: property_name = "Saturation";  break;
			case cv::CAP_PROP_HUE: property_name = "Hue";  break;
			case cv::CAP_PROP_GAIN: property_name = "Gain";  break;
			case cv::CAP_PROP_EXPOSURE: property_name = "Exposure";   break;
			case cv::CAP_PROP_SHARPNESS: property_name = "Sharpness";  break;
			case cv::CAP_PROP_GAMMA: property_name = "Gamma";  break;
			default: property_name = "<not-supported>"; break;
		}
	}
private:
	std::string property_name;
};

class CameraPropertiesHolder : public QWidget
{
	Q_OBJECT

public:
	CameraPropertiesHolder(cv::VideoCapture* cap, QMutex* mutex, QWidget*parent = Q_NULLPTR);
	~CameraPropertiesHolder();

	void AddPropertyWidget();

private:
	Ui::CameraPropertiesHolder ui;

	cv::VideoCapture *m_Cap;
	QMutex* m_Mutex;
};
