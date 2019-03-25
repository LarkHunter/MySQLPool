#ifndef MONTHPLAN_H
#define MONTHPLAN_H

#include <QWidget>
#include "ui_monthplan.h"
#include <set>

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

public:
	bool LoadResource(const char* pszPlancfg); // ������Դ

	bool InitListWidget(QString& qstrInfo); // ��ʼ��planlist

private:
	Ui::monthPlan ui;

public:
	std::set<int> m_iSetItem;
private:
	int m_iMonth;
};

#endif // MONTHPLAN_H
