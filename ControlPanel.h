#pragma once

#include <QWidget>
#include <QObject>
#include "ui_ControlPanel.h"

class ControlPanel : public QWidget
{
	Q_OBJECT

public:
	ControlPanel(QWidget *parent = Q_NULLPTR);
	~ControlPanel();

	Ui::ControlPanel GetUi();

private:
	Ui::ControlPanel ui;
};
