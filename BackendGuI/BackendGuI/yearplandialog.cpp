#include "yearplandialog.h"
#include<QDebug>
#include <QMessageBox>

#define D_YEAR_PLAN "yearPlan.txt"
YearPlanDialog::YearPlanDialog(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_cTimer = new QTimer(this);

	this->setWindowTitle(QString::fromLocal8Bit("���溣�� "));
	this->setWindowIcon(QIcon("wheet.png"));

	connect(ui.addButton,SIGNAL(clicked()),this,SLOT(onAddPlanBtnclicked()));

	bool bResult = connect(ui.listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(onDoubleClickedDelete()));

	bResult = connect(ui.listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),this, SLOT(onDoubleClickedDelete()));

	connect(m_cTimer,SIGNAL(timeout()),this,SLOT(onTimeOut()));

	ui.listWidget->setSortingEnabled(true); // �Զ�����

	this->setWindowTitle(QString::fromLocal8Bit("���溣����ƻ� "));
	this->setWindowIcon(QIcon("wheet.png"));

	m_nClickTimes = 0;

	LoadResource();
}

YearPlanDialog::~YearPlanDialog()
{

}

/*--------------------------------------------------------------------
** ���� : LoadResource
**--------------------------------------------------------------------
** ���� : ������Դ
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.03.24		Mark
**-------------------------------------------------------------------*/
bool YearPlanDialog::LoadResource()
{

	QFile file(D_YEAR_PLAN);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return false;
	}

	QTextStream in(&file);
	in.setCodec("UTF-8");
	
	if(in.atEnd())
	{
		ui.listWidget->clear();
		
		m_mapItemYearPlan.clear();

		return false;
	}

	while(!in.atEnd()) 
	{
		QString line = in.readLine();

		InitListWidget(line);
	}
	return true;
}
/*--------------------------------------------------------------------
** ���� : InitListWidget
**--------------------------------------------------------------------
** ���� : ��ʼ��list�ؼ�
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.03.24		Mark
**-------------------------------------------------------------------*/
bool YearPlanDialog::InitListWidget(QString& qstrInfo)
{
	if(qstrInfo.isEmpty())
	{
		return false;
	}
	QStringList list = qstrInfo.split(":");

	QString qstrNumber = list[0]; 
	QString qstrText = list[1]; 

	int iKey = qstrNumber.toInt();

	m_mapItemYearPlan.insert(std::make_pair(iKey,qstrText));
// 	bool bExist = DataOperation::isPlanExist(m_mapItemYearPlan, iKey);
// 	if(bExist)
// 	{
// 		QString QsTitle = QString::fromLocal8Bit("�ظ�");
// 		QString QsContent = QString::fromLocal8Bit("��ǰ��ŵļƻ��Ѿ�����");
// 		QMessageBox::about(NULL, QsTitle, QsContent);
// 
// 		return false;
// 	}
	
	ui.listWidget->insertItem(0, qstrInfo);

	return true;
}

/*--------------------------------------------------------------------
** ���� : onAddPlanBtnclicked
**--------------------------------------------------------------------
** ���� : �¼���Ӧ�ۺ���:�����ƻ�
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.03.24		Mark
**-------------------------------------------------------------------*/
void YearPlanDialog::onAddPlanBtnclicked()
{
	QString qsPlan = ui.planLineEdit->text();

	int iKey = DataOperation::QueryPlanKey(m_mapItemYearPlan);

	bool bData = DataOperation::addPlan(m_mapItemYearPlan, iKey, qsPlan); // ���浽����������
	if (!bData)
	{
		return;
	}

	QString qstrPlan;
	qstrPlan = QString::number(iKey);

	qstrPlan.append(":");
	qstrPlan.append(qsPlan);

	qDebug() <<"qstrPlan"<< qstrPlan;

	ui.listWidget->insertItem(0, qstrPlan); // ��ʾ��������
	
	FileOpration::addPlanItem(D_YEAR_PLAN, qstrPlan); // ���浽�ļ�����

	ui.planLineEdit->clear();
}

void YearPlanDialog::onPlanWidgetBtnclicked()
{
	m_nClickTimes += 1;

	qDebug() << "PlanWidgetBtnclicked ...";
	m_cTimer->start(200);
}

/*--------------------------------------------------------------------
** ���� : onDoubleClickedDelete
**--------------------------------------------------------------------
** ���� : �¼���Ӧ�ۺ���:ɾ���ƻ�
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.04.01		Mark
**-------------------------------------------------------------------*/
void YearPlanDialog::onDoubleClickedDelete()
{
	int iRow = ui.listWidget->currentRow();
	int iKey = iRow + 1;

	DataOperation::deletePlan(m_mapItemYearPlan,iKey); // ɾ���������еļƻ�

	FileOpration::UpdatePlanFile(D_YEAR_PLAN,m_mapItemYearPlan); // �����ļ��еļƻ�

	DataOperation::renewPlanItem(D_YEAR_PLAN, m_mapItemYearPlan); // ���µ�����

	LoadResource(); // ������Դ

	qDebug() << "iRow = "<< iRow<< endl;
}

/*--------------------------------------------------------------------
** ���� : onTimeOut
**--------------------------------------------------------------------
** ���� : �¼���Ӧ�ۺ���:��ʱ����ʱ��Ӧ
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.03.30		Mark
**-------------------------------------------------------------------*/
void YearPlanDialog::onTimeOut()
{
	m_cTimer->stop();
	if (1 == m_nClickTimes) {
		qDebug() << "click event" << endl;
		//TODO Click respond.
	}
	else if (2 == m_nClickTimes) {
		qDebug() << "double click event" << endl;
		//TODO Double click respond.
	}
	m_nClickTimes = 0;
}
