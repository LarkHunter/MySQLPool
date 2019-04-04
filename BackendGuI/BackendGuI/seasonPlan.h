#pragma once

#include <QWidget>
#include "ui_seasonPlan.h"
#include "DataOpration/DataOperation.h"
#include "FileOpration/FileOpration.h"

#include <set>
#include <map>

typedef std::map<int, QString> MapPlanSeason; // �������������ÿ�µļƻ�

typedef std::map<int, MapPlanSeason> MapSeasonSum;

class seasonPlan : public QWidget
{
	Q_OBJECT

public:
	seasonPlan(QWidget *parent = Q_NULLPTR);
	~seasonPlan();

public:

	// �Ѽƻ���ʾ��List�ؼ���
	bool ShowListWidget(const char* pszPlancfg);

	// ������Դ
	bool LoadResource(const char* pszPlancfg); 

	// ��ʼ���ƻ�
	bool InitListWidget(QString& qstrInfo); // ��ʼ��planlist

	// ���¼ƻ�
	bool UpdateListWidget(QString& qstrInfo);

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

	// ɾ��
	void onDeletePlan();
public:
	
	// ȡ����ǰkey
	int  QueryQurrentKey();

	// ���浽����������
	void SavePlanOnMap(int iKey,QString&qstrPlan);

	// ȡ�õ�ǰ�ļ�
	const char* QuerySeasonPlanFile();
public:
	std::set<int> m_iSetItem;

	MapSeasonSum m_MapSeasonSum; // �����ܼƻ�
private:
	int m_iSeason;
private:
	Ui::seasonPlan ui;

};
