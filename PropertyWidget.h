#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QSlider>
#include <QLabel>
#include <QLineEdit>
#include "ui_PropertyWidget.h"

class PropertyWidget : public QWidget
{
public:
	PropertyWidget(QWidget* parent, QString name, int min, int max, int value);
	~PropertyWidget();

private:
	Ui::PropertyWidget ui;
};