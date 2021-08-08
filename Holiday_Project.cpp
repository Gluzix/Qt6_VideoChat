#include "Holiday_Project.h"
#include <QGraphicsAnchorLayout>

Holiday_Project::Holiday_Project(QWidget *parent)
    : QMainWindow(parent)
    , m_DeviceId(0)
    , m_ApiId(cv::CAP_ANY)
{
    ui.setupUi(this);
     
    m_Scene = new QGraphicsScene();
    m_PixmapItem = new QGraphicsPixmapItem();
    m_Scene->addItem(m_PixmapItem);
    ui.GraphicsView->setScene(m_Scene);

    m_pControlPanel = new ControlPanel(this);
    connect(m_pControlPanel->GetUi().ButtonStart, SIGNAL(clicked()), this, SLOT(OnStartButtonClicked()));
    connect(m_pControlPanel->GetUi().ButtonStop, SIGNAL(clicked()), this, SLOT(OnStopButtonClicked()));

    m_Gatherer = new ImageGatherer(&m_Cap, &m_Mutex);
    connect(m_Gatherer, SIGNAL(PassImage(QImage)), this, SLOT(OnImage(QImage)), Qt::QueuedConnection);
    connect(&m_Thread, SIGNAL(started()), m_Gatherer, SLOT(ProcessImage()));
    m_Gatherer->moveToThread(&m_Thread);

    m_CameraPropertiesHolder = new CameraPropertiesHolder(&m_Cap, &m_Mutex);

    m_Thread.start();
}

Holiday_Project::~Holiday_Project()
{
    m_Gatherer->StopThread();
    m_Thread.quit();
    m_Thread.wait();

    delete m_Gatherer;
    m_Gatherer = nullptr;

    delete m_Scene;
    m_Scene = nullptr;
}

void Holiday_Project::PrepareCapturer()
{
    QMutexLocker locker(&m_Mutex);
    m_Cap.open(m_DeviceId);

    if (!m_Cap.isOpened())
    {
        qCritical() << "Camera was not opened";
    }
    qInfo() << "Camera was successfully opened";
}

void Holiday_Project::OnStartButtonClicked()
{
    qInfo() << "Start called from thread: " << QThread::currentThread();
    m_Gatherer->StartAcquisition();
}

void Holiday_Project::OnStopButtonClicked()
{
    m_Gatherer->StopAcquisition();
}

void Holiday_Project::resizeEvent(QResizeEvent* event)
{
    int x = this->width() / 2 - m_pControlPanel->width() / 2;
    int y = this->height() - m_pControlPanel->height();
    m_pControlPanel->setGeometry(x, y, m_pControlPanel->width(), m_pControlPanel->height());
    QWidget::resizeEvent(event);
}

void Holiday_Project::OnImage(QImage image)
{
    m_Scene->setSceneRect(0, 0, image.width(), image.height());
    QPixmap pixmap = QPixmap::fromImage(image);
    m_PixmapItem->setPixmap(pixmap);
    m_Scene->update();
}
