#pragma once

#include <QtWidgets/QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QObject>
#include <QThread>
#include <QGraphicsProxyWidget>
#include "CustomGraphicsView.h"
#include "ImageGatherer.h"
#include "ControlPanel.h"
#include "CameraPropertiesHolder.h"
#include "ui_Holiday_Project.h"

class Holiday_Project : public QMainWindow
{
    Q_OBJECT
public:
    Holiday_Project(QWidget *parent = Q_NULLPTR);
    ~Holiday_Project();

    void PrepareCapturer();


private slots:
    void OnImage(QImage image);
    void OnStartButtonClicked();
    void OnStopButtonClicked();

private:
    virtual void resizeEvent(QResizeEvent* event) override;

    Ui::Holiday_ProjectClass ui;
    ControlPanel *m_pControlPanel;
    QGraphicsScene *m_Scene;
    QGraphicsPixmapItem *m_PixmapItem;
    ImageGatherer *m_Gatherer;
    CameraPropertiesHolder* m_CameraPropertiesHolder;
    QThread m_Thread;

    cv::VideoCapture m_Cap;
    QMutex m_Mutex;

    int m_DeviceId;
    int m_ApiId;
};
