#ifndef MONTHPLAN_H
#define MONTHPLAN_H

#include <QWidget>
#include "ui_monthplan.h"
#include "DataOpration/DataOperation.h"
#include "FileOpration/FileOpration.h"

class monthPlan : public QWidget
{
	Q_OBJECT

public:
	monthPlan(QWidget *parent = 0);
	~monthPlan();

	public slots:
	
	// һ��
	void onJanBtnclicked();

	// ����
	void onFebBtnclicked();

	// ����
	void onMarBtnclicked();

	// ����
	void onAprBtnclicked();

	// ����
	void onMayBtnclicked();

	// ����
	void onJunBtnclicked();

	// ����
	void onJulBtnclicked();

	// ����
	void onAugBtnclicked();

	// ����
	void onSepBtnclicked();

	// ʮ��
	void onOctBtnclicked();

	// ʮһ��
	void onNovBtnclicked();

	// ʮ����
	void onDecBtnclicked();

	// ����
	void onAddBtnclicked();

	// ɾ��
	void onDoubleClickedDelete();

public:
	bool LoadResource(const char* pszPlancfg); // ������Դ

	bool InitListWidget(QString& qstrInfo, MapItemPlan& mapItemPlan); // ��ʼ��planlist

	// ȡ�õ�ǰ�ļ�
	const char* QuerySeasonPlanFile();

	// ȡ�õ�ǰ������
	void QueryQurrentMap(MapItemPlan& mapItemPlan);

	// ���浽��ǰ����������
	void SaveMonthPlanMap(int iKey,QString & qstrPlan);

private:
	Ui::monthPlan ui;

public:

	//MapItemPlan m_mapMonthPlan; //
	MapItemPlan m_mapPlanJan; // 1�¼ƻ� 
	MapItemPlan m_mapPlanFeb; // 2�¼ƻ� 
	MapItemPlan m_mapPlanMar; // 3�¼ƻ� 

	MapItemPlan m_mapPlanApr; // 4�¼ƻ� 
	MapItemPlan m_mapPlanMay; // 5�¼ƻ� 
	MapItemPlan m_mapPlanJun; // 6�¼ƻ� 

	MapItemPlan m_mapPlanJul; // 7�¼ƻ� 
	MapItemPlan m_mapPlanAug; // 8�¼ƻ� 
	MapItemPlan m_mapPlanSep; // 9�¼ƻ� 

	MapItemPlan m_mapPlanOct; // 10�¼ƻ� 
	MapItemPlan m_mapPlanNov; // 11�¼ƻ� 
	MapItemPlan m_mapPlanDec; // 12�¼ƻ� 
private:
	int m_iMonth;
};

#endif // MONTHPLAN_H
