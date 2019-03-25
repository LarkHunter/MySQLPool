#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <QTimer>
#include "ui_BackendGuI.h"
#include "YearPlanDialog.h"
#include "loginwarn.h"
#include "seasonPlan.h"
#include "monthplan.h"
class BackendGuI : public QMainWindow
{
	Q_OBJECT

public:
	BackendGuI(QWidget *parent = Q_NULLPTR);
	
	public slots:
	void onAccountBtnclicked();
	void onResetBtnClicked(); // ����
	void onYearPlanBtnclicked(); // ��ȼƻ�
	void onSeasonPlanBtnclicked(); // ���ȼƻ�
	void onMonthPlanBtnclicked(); // ÿ�¼ƻ�

	void onTimeOut();

public:
	//QPushButton *yearPlanButton = new QPushButton;
	QTimer *m_cTimer;
	loginWarn m_loginWarn;

	YearPlanDialog yearPlanDialog; // ��ȼƻ�
	seasonPlan m_seasonPlanDiglog; //���ȼƻ�
	monthPlan m_monthPlanDialog; // ÿ�¼ƻ�
private:
	int m_nClickTimes;

	int m_nErrorCount; // ���������������Ĵ��� 
private:
	Ui::BackendGuIClass ui;
};
