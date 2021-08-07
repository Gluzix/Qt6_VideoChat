#pragma once

#include <QWidget>
#include <QObject>
#include <QGraphicsView>

class CustomGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	CustomGraphicsView(QWidget*parent = Q_NULLPTR);
	~CustomGraphicsView();
};
