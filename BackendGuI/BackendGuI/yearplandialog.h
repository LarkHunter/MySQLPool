#ifndef YEARPLANDIALOG_H
#define YEARPLANDIALOG_H

#include <QWidget>
#include "ui_yearplandialog.h"
#include <QFile>
#include <QTimer>

#include<set>

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

	// ����ƻ�
	void onPlanWidgetBtnclicked();
public:
	std::set<int> m_iSetItem;

	QTimer *m_cTimer;

private:
	Ui::YearPlanDialog ui;

private:
	int m_nClickTimes;

};

#endif // YEARPLANDIALOG_H
