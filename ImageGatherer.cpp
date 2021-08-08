#include "ImageGatherer.h"
#include <QThread>

ImageGatherer::ImageGatherer(cv::VideoCapture* cap, QMutex* mutex, QObject* parent)
	: m_bIsAcquiring (false)
	, m_bIsThreadActive(true)
	, m_Capture(cap)
	, m_Mutex(mutex)
{
}

ImageGatherer::~ImageGatherer()
{
	ReleaseCapturer();
}

void ImageGatherer::ReleaseCapturer()
{
	m_Frame.release();
}

void ImageGatherer::StartAcquisition()
{
	QMutexLocker locker(m_Mutex);
	m_bIsAcquiring = true;
}

void ImageGatherer::StopAcquisition()
{
	QMutexLocker locker(m_Mutex);
	m_bIsAcquiring = false;
}

void ImageGatherer::StopThread()
{
	QMutexLocker locker(m_Mutex);
	m_bIsThreadActive = false; 
}

void ImageGatherer::ProcessImage()
{
	while (true)
	{
		QMutexLocker locker(m_Mutex);
		if (m_bIsAcquiring)
		{
			m_Capture->read(m_Frame);
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
