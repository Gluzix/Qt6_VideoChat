#include "ImageGatherer.h"
#include <QThread>

ImageGatherer::ImageGatherer(QObject* parent)
	: m_DeviceId (0)
	, m_ApiId (cv::CAP_ANY)
	, m_bIsAcquiring (false)
	, m_bIsThreadActive(true)
{
}

ImageGatherer::~ImageGatherer()
{
	ReleaseCapturer();
}

bool ImageGatherer::PrepareCapturer()
{
	QMutexLocker locker(&m_Mutex);

	m_Capture.open(m_DeviceId);

	if (!m_Capture.isOpened())
	{
		qCritical() << "Camera was not opened";
		return false;
	}
	qInfo() << "Camera was successfully opened";
	return true;
}

void ImageGatherer::ReleaseCapturer()
{
	m_Frame.release();
	m_Capture.release();
}

void ImageGatherer::StartAcquisition()
{
	QMutexLocker locker(&m_Mutex);
	m_bIsAcquiring = true;
}

void ImageGatherer::StopAcquisition()
{
	QMutexLocker locker(&m_Mutex);
	m_bIsAcquiring = false;
}

void ImageGatherer::StopThread()
{
	m_bIsThreadActive = false; 
}

void ImageGatherer::ProcessImage()
{
	while (true)
	{
		QMutexLocker locker(&m_Mutex);
		if (m_bIsAcquiring)
		{
			m_Capture.read(m_Frame);
			QImage imgIn = QImage((uchar*)m_Frame.data, m_Frame.cols, m_Frame.rows, m_Frame.step, QImage::Format_RGB888);
			emit PassImage(imgIn);
		}
		else
		{
			QThread::msleep(500);
		}
		 
		if (!m_bIsThreadActive)
		{
			break;
		}
	}
}
