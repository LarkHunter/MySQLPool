#include "yearplandialog.h"
#include<QDebug>
#include <QMessageBox>

YearPlanDialog::YearPlanDialog(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_cTimer = new QTimer(this);

	this->setWindowTitle(QString::fromLocal8Bit("���溣�� "));
	this->setWindowIcon(QIcon("wheet.png"));

	connect(ui.addButton,SIGNAL(clicked()),this,SLOT(onAddPlanBtnclicked()));

	bool bResult = connect(ui.listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(onPlanWidgetBtnclicked()));

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

	QFile file("yearPlan.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return false;
	}

	QTextStream in(&file);
	in.setCodec("UTF-8");
	while(!in.atEnd()) 
	{
		QString line = in.readLine();

		InitListWidget(line);
		//process_line(line);
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

	int iNumber = qstrNumber.toInt();
	std::set<int>::iterator itSet = m_iSetItem.find(iNumber);
	if(itSet != m_iSetItem.end())
	{
		QString QsTitle = QString::fromLocal8Bit("�ظ�");
		QString QsContent = QString::fromLocal8Bit("��ǰ��ŵļƻ��Ѿ�����");
		QMessageBox::about(NULL, QsTitle, QsContent);

		return false;
	}

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
	int inumber = ui.numEdit->text().toInt();
	QString qsPlan = ui.planLineEdit->text();

	// ��֤��ǰ����Ƿ����
	std::set<int>::iterator itSet = m_iSetItem.find(inumber);
	if(itSet != m_iSetItem.end())
	{
		QString QsTitle = QString::fromLocal8Bit("�ظ�");
		QString QsContent = QString::fromLocal8Bit("��ǰ��ŵļƻ��Ѿ�����");
		QMessageBox::about(NULL, QsTitle, QsContent);

		return ;
	}

	QString qstrPlan;
	qstrPlan = QString::number(inumber);

	qstrPlan.append(":");
	qstrPlan.append(qsPlan);

	qDebug() <<"qstrPlan"<< qstrPlan;
	ui.listWidget->insertItem(0, qstrPlan);

	m_iSetItem.insert(inumber); // ���浱ǰ���

	QFile fileout("yearPlan.txt");

	if(!fileout.open(QIODevice::Append | QIODevice::Text))
	{
		qDebug() << "Open failed";
		return;
	}	
	
	qstrPlan.append("\n");
	std::string strPlan = qstrPlan.toStdString();
	const char* pszPlan = strPlan.c_str();

	fileout.write(pszPlan);

	
	//ui.listWidget->scrollToBottom();
	//ui.listWidget->insertItem(0, QString::fromLocal8Bit("2������СĿ��:�ٻ���һ����"));
	//ui.listWidget->scrollToBottom();
	

	ui.numEdit->clear();
	ui.planLineEdit->clear();
}

void YearPlanDialog::onPlanWidgetBtnclicked()
{
	m_nClickTimes += 1;

	qDebug() << "PlanWidgetBtnclicked ...";
	m_cTimer->start(200);
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
