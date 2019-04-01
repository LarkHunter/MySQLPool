#ifndef YEARPLANDIALOG_H
#define YEARPLANDIALOG_H

#include <QWidget>
#include "ui_yearplandialog.h"
#include <QFile>
#include <QTimer>
#include <map>
#include "DataOpration/DataOperation.h"
#include "FileOpration/FileOpration.h"

/*---------------------------------------------------------------------------
** ���� : YearPlanDialog
**---------------------------------------------------------------------------
** ���� : ��ƻ�
**---------------------------------------------------------------------------
** Date			Name
** 2019.04.01	Mark
**---------------------------------------------------------------------------*/
class YearPlanDialog : public QWidget
{
	Q_OBJECT

public:
	YearPlanDialog(QWidget *parent = 0);
	~YearPlanDialog();

public:
	bool LoadResource(); // ������Դ

	bool InitListWidget(QString& qstrInfo); // ��ʼ��planlist

	public slots:

	// �����ƻ�
	void onAddPlanBtnclicked();

	// �����޸�(������)
	void onPlanWidgetBtnclicked();

	// ˫���Ҽ�ɾ��
	void onDoubleClickedDelete();

	// ��ʱ
	void onTimeOut();
public:
	//std::set<int> m_iSetItem;

	MapItemPlan m_mapItemYearPlan;
	QTimer *m_cTimer;

private:
	Ui::YearPlanDialog ui;

private:
	int m_nClickTimes;

};

#endif // YEARPLANDIALOG_H
