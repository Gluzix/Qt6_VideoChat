#include "PropertyWidget.h"
#include <QValidator>

PropertyWidget::PropertyWidget(QWidget*parent, QString name, int min, int max, int value)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.m_LabelName->setText(name);
	ui.m_HorizontalSlider->setMinimum(min);
	ui.m_HorizontalSlider->setMaximum(max);
	ui.m_HorizontalSlider->setValue(value);
	ui.m_LineEdit->setValidator(new QIntValidator(min, max));
}

PropertyWidget::~PropertyWidget()
{
}
