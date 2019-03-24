#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <QTimer>
#include "ui_BackendGuI.h"
#include "YearPlanDialog.h"

class BackendGuI : public QMainWindow
{
	Q_OBJECT

public:
	BackendGuI(QWidget *parent = Q_NULLPTR);
	
	public slots:
	void onAccountBtnclicked();
	void onResetBtnClicked(); // ����
	void onYearPlanBtnclicked(); // ��ȼƻ�

	void onTimeOut();

public:
	//QPushButton *yearPlanButton = new QPushButton;
	QTimer *m_cTimer;
	YearPlanDialog yearPlanDialog;
private:
	int m_nClickTimes;

private:
	Ui::BackendGuIClass ui;
};
