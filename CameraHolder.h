#pragma once

#include <QObject>
#include <opencv2/videoio.hpp>
#include <opencv2/core.hpp>
#include "ImageGatherer.h"

class CameraHolder : public QObject
{
	Q_OBJECT

public:
	CameraHolder(QObject *parent);
	~CameraHolder();

	void EnumerateCameraProperties();
};
