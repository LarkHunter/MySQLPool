#pragma once

#include <QWidget>
#include "ui_seasonPlan.h"

#include <set>

class seasonPlan : public QWidget
{
	Q_OBJECT

public:
	seasonPlan(QWidget *parent = Q_NULLPTR);
	~seasonPlan();

public:
	bool LoadResource(const char* pszPlancfg); // ������Դ

	bool InitListWidget(QString& qstrInfo); // ��ʼ��planlist

public slots:

	// ����
	void onSpringBtnclicked();
	
	// �ļ�
	void onSummerBtnclicked();

	// �＾
	void onAutumnBtnclicked();

	// ����
	void onWinterBtnclicked();

	// ����
	void onAddBtnclicked();
public:
	std::set<int> m_iSetItem;
private:
	int m_iSeason;
private:
	Ui::seasonPlan ui;

};
