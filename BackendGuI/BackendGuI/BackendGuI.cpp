#include "BackendGuI.h"
#include <QDebug>
BackendGuI::BackendGuI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.confirmBtn->setStyleSheet("color:red");

	yearPlanButton->setGeometry(10, 10, 200, 200);

	connect(ui.confirmBtn, SIGNAL(clicked()), this, SLOT(onAccountBtnclicked()));

}
/*--------------------------------------------------------------------
** ���� : onAccountBtnclicked
**--------------------------------------------------------------------
** ���� : �¼���Ӧ�ۺ���
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 18.06.28		Mark
**-------------------------------------------------------------------*/
void BackendGuI::onAccountBtnclicked()
{
	qDebug() << "..";
}
