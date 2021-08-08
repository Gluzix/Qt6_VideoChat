#include "CameraPropertiesHolder.h"

CameraPropertiesHolder::CameraPropertiesHolder(cv::VideoCapture* cap, QMutex* mutex, QWidget* parent)
	: QWidget(parent)
	, m_Cap(cap)
	, m_Mutex(mutex)
{
	ui.setupUi(this);
}

CameraPropertiesHolder::~CameraPropertiesHolder()
{
}

void CameraPropertiesHolder::AddPropertyWidget()
{
	QMutexLocker locker(m_Mutex);
	for (int i = 0; i < 53; i++)
	{
		double value = m_Cap->get(i);
		if (value != 0)
		{
			Property prop(i);
			qInfo() << QString::fromStdString(prop.GetPropertyName());
		}
	}
}