#include "yearplandialog.h"

YearPlanDialog::YearPlanDialog(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromLocal8Bit("���溣�� "));
	this->setWindowIcon(QIcon("wheet.png"));

}

YearPlanDialog::~YearPlanDialog()
{

}
