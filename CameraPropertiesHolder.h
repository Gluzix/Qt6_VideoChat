#pragma once

#include <QObject>
#include <QWidget>
#include <QMutex>
#include <QThread>
#include <opencv2/videoio.hpp>
#include <opencv2/core.hpp>
#include "CameraPropertiesHolderWorker.h"
#include "ui_CameraPropertiesHolder.h"

class CameraPropertiesHolder : public QWidget
{
	Q_OBJECT

public:
	CameraPropertiesHolder(cv::VideoCapture* cap, QMutex* mutex, QWidget*parent = Q_NULLPTR);
	~CameraPropertiesHolder();

	void ReadCameraProperties();

public slots:
	void AddPropertyWidget(QString name);

private:
	Ui::CameraPropertiesHolder ui;

	cv::VideoCapture *m_Cap;
	QMutex* m_Mutex;
};
