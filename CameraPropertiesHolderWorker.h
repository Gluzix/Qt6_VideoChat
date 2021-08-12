#include <QObject>
#include <QMutex>
#include <QThread>
#include <opencv2/videoio.hpp>
#include <opencv2/core.hpp>

const unsigned int NUMBER_OF_CV_FEATURES = 53;

class CameraPropertiesHolderWorker : public QObject
{
	Q_OBJECT
public:
	CameraPropertiesHolderWorker(cv::VideoCapture* cap, QMutex* mutex, QObject* parent = nullptr);
	~CameraPropertiesHolderWorker();

public slots:
	void Process();

signals:
	void SendPropertyName(QString name);

private:
	std::string CheckParameterByIndex(int index);

	cv::VideoCapture* m_Cap;
	QMutex* m_Mutex;

};
