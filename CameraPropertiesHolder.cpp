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

void CameraPropertiesHolder::ReadCameraProperties()
{
	CameraPropertiesHolderWorker* worker = new CameraPropertiesHolderWorker(m_Cap, m_Mutex);
	QThread *thread = new QThread();

	connect(worker, SIGNAL(SendPropertyName(QString)), this, SLOT(ddPropertyWidget(QString)));
	connect(thread, SIGNAL(started()), worker, SLOT(Process()));
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	connect(thread, SIGNAL(finished()), worker, SLOT(deleteLater()));
	worker->moveToThread(thread);
	thread->start();
}

void CameraPropertiesHolder::AddPropertyWidget(QString name)
{
	qInfo() << "PropertyName: " << name;
}