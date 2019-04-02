#include "BackendGuI.h"
#include <QDebug>
#include <QMessageBox>

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
	connect(ui.seasonPlanBtn, SIGNAL(clicked()), this, SLOT(onSeasonPlanBtnclicked()));
	connect(ui.monthPlanBtn, SIGNAL(clicked()), this, SLOT(onMonthPlanBtnclicked()));

	connect(ui.resetBtn, SIGNAL(clicked()),this,SLOT(onResetBtnClicked()));
	connect(ui.confirmBtn, SIGNAL(clicked()), this, SLOT(onAccountBtnclicked()));

	ui.yearPlanBtn->setEnabled(false);
	ui.seasonPlanBtn->setEnabled(false);
	ui.monthPlanBtn->setEnabled(false);

	m_nErrorCount = 3;
	//connect(m_cTimer, SIGNAL(timeout()),this,SLOT(onTimeOut()));
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
** 19.03.24		Mark
**-------------------------------------------------------------------*/
void BackendGuI::onAccountBtnclicked()
{
	m_nErrorCount--;
	
	qDebug() << "CWinButton::clicked" << endl;
	int iAccount = ui.accountEdit->text().toInt();
	int iPwd = ui.pwdEdit->text().toInt();
	if(1995 != iAccount ||
		1112 != iPwd)
	{
		if(m_nErrorCount <= 0)
		{
			this->hide();
			m_loginWarn.show();
			return;
		}

		ui.accountEdit->clear();
		ui.pwdEdit->clear();
		QString QsTitle = QString::fromLocal8Bit("���棡");

		QString QsContent = QString::fromLocal8Bit("�����С�");
		QString qstrCount = QString::number(m_nErrorCount);
		QString QsChance = QString::fromLocal8Bit("���λ��᳢��\n");
		QString qsWarnContent = QString::fromLocal8Bit("���Ǳ��˵�¼��������������");
		QsContent.append(qstrCount);
		QsContent.append(QsChance);
		QsContent.append(qsWarnContent);
		
		QMessageBox::about(NULL, QsTitle, QsContent);

		//m_loginWarn.close();
	}
	else
	{
		ui.yearPlanBtn->setEnabled(true);
		ui.seasonPlanBtn->setEnabled(true);
		ui.monthPlanBtn->setEnabled(true);

		ui.confirmBtn->setEnabled(false);
		ui.resetBtn->setEnabled(false);
	}

	ui.accountEdit->clear();
	ui.pwdEdit->clear();
	//m_nClickTimes++;
	//m_cTimer->start(200);

	

	qDebug() << "..";
}

void BackendGuI::onResetBtnClicked()
{
	ui.accountEdit->clear();
	ui.pwdEdit->clear();
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
** 19.03.24		Mark
**-------------------------------------------------------------------*/
void BackendGuI::onYearPlanBtnclicked()
{
	qDebug() << "onYearPlanBtnclicked" << endl;
	yearPlanDialog.show();
}
/*--------------------------------------------------------------------
** ���� : onSeasonPlanBtnclicked
**--------------------------------------------------------------------
** ���� : �¼���Ӧ�ۺ���
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.03.25		Mark
**-------------------------------------------------------------------*/
void BackendGuI::onSeasonPlanBtnclicked()
{
	m_seasonPlanDiglog.show();
}
/*--------------------------------------------------------------------
** ���� : onSeasonPlanBtnclicked
**--------------------------------------------------------------------
** ���� : �¼���Ӧ�ۺ���
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.03.25		Mark
**-------------------------------------------------------------------*/
void BackendGuI::onMonthPlanBtnclicked()
{
	m_monthPlanDialog.show();
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
** 19.03.24		Mark
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
