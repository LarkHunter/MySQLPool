#include "BackendGuI.h"
#include <QDebug>
BackendGuI::BackendGuI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.confirmBtn->setStyleSheet("color:red");

	//yearPlanButton->setGeometry(10, 10, 200, 200);
	this->setWindowTitle(QString::fromLocal8Bit("���溣�� "));
	//this->setWindowTitle(QString::fromUtf8("�ƻ�������@Mark "));
	this->setWindowIcon(QIcon("wheet.png"));

	m_nClickTimes = 0;

	m_cTimer = new QTimer(this);

	connect(ui.yearPlanBtn, SIGNAL(clicked()), this, SLOT(onYearPlanBtnclicked()));
	connect(ui.confirmBtn, SIGNAL(clicked()), this, SLOT(onAccountBtnclicked()));

	connect(m_cTimer, SIGNAL(timeout()),this,SLOT(onTimeOut()));
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
	qDebug() << "CWinButton::clicked" << endl;
	m_nClickTimes++;
	m_cTimer->start(200);

	//qDebug() << "..";
}
/*--------------------------------------------------------------------
** ���� : onYearPlanBtnclicked
**--------------------------------------------------------------------
** ���� : �¼���Ӧ�ۺ���
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 18.06.28		Mark
**-------------------------------------------------------------------*/
void BackendGuI::onYearPlanBtnclicked()
{
	qDebug() << "onYearPlanBtnclicked" << endl;
}

/*--------------------------------------------------------------------
** ���� : onConfirmBtnclicked
**--------------------------------------------------------------------
** ���� : �¼���Ӧ�ۺ���
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 18.06.28		Mark
**-------------------------------------------------------------------*/
void BackendGuI::onTimeOut()
{
	//qDebug() << "...";
	qDebug() << "CWinButton::slotTimerTimeOut" << endl;
	m_cTimer->stop();
	if (1 == m_nClickTimes) {
		qDebug() << "click event" << endl;
		//TODO Click respond.
	}
	else if (2 == m_nClickTimes) {
		qDebug() << "double click event" << endl;
		//TODO Double click respond.
	}
	else if(3 == m_nClickTimes)
	{
		qDebug() << "Triple  click event" << endl;
	}
	m_nClickTimes = 0;

}
