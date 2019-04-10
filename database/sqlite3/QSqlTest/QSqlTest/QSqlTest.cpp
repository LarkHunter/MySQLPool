#include "QSqlTest.h"
#include <string.h>
#include <QDebug>
#define  D_TABLE "LocalTable"

QSqlService* QSqlTest::m_sqlService = NULL;

QSqlTest::QSqlTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	bool bResult = connect(ui.addButton, SIGNAL(clicked()),this,SLOT(onAddBtn()) );

	bResult = connect(ui.showButton, SIGNAL(clicked()), this, SLOT(onReviewInfo()));

	m_sqlService = new QSqlService();

	m_sqlService->StartService("test", D_TABLE);
}
/*---------------------------------------------------------------------------
** ���� : onAddBtn
** ���� : ��������
**---------------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**---------------------------------------------------------------------------
** Date			Name
** 19.04.08		��ΰ
**---------------------------------------------------------------------------*/
void QSqlTest::onAddBtn()
{
	QString qstrPlan = ui.lineEdit->text();
	if(qstrPlan.isEmpty())
	{
		return;
	}

	std::string strPlan = qstrPlan.toStdString();

	const char* spzPlan = strPlan.c_str();

	m_sqlService->addItem(D_TABLE,spzPlan);

}
/*---------------------------------------------------------------------------
** ���� : onReviewInfo
** ���� : �鿴��Ϣ
**---------------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**---------------------------------------------------------------------------
** Date			Name
** 19.04.08		��ΰ
**---------------------------------------------------------------------------*/
void QSqlTest::onReviewInfo()
{
	VecItemInfo vecInfo;
	m_sqlService->QueryInfo(D_TABLE, vecInfo);

	VecItemInfo::iterator itInfo = vecInfo.begin();
	for(; itInfo!= vecInfo.end();itInfo++)
	{
		std::string strInfo = (*itInfo);
		//qDebug() << (*itInfo).c_str() << endl;;
	}
}
