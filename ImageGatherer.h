#pragma once

#include <QObject>
#include <QImage>
#include <QMutex>
#include <QDebug>
#include <opencv2/videoio.hpp>
#include <opencv2/core.hpp>

class ImageGatherer : public QObject
{
	Q_OBJECT
public:
	ImageGatherer(cv::VideoCapture* cap, QMutex *mutex, QObject* parent = Q_NULLPTR);
	~ImageGatherer();

	void ReleaseCapturer();
	void StartAcquisition();
	void StopAcquisition();
	void StopThread();

public slots:
	void ProcessImage();

signals:
	void PassImage(QImage image);

private:
	QMutex *m_Mutex;
	cv::Mat m_Frame;
	cv::VideoCapture *m_Capture;
	bool m_bIsAcquiring;
	bool m_bIsThreadActive;
};

