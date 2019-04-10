#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QSqlTest.h"
#include "Service/QSqlService.h"
#include "QYearPlan.h"

class QSqlTest : public QMainWindow
{
	Q_OBJECT

public:
	QSqlTest(QWidget *parent = Q_NULLPTR);

private:
	Ui::QSqlTestClass ui;

public slots:

	// �ۺ���:������Ŀ
	void onAddBtn(); 

	// �ۺ���:�鿴
	void onReviewInfo();

public:

	static QSqlService *m_sqlService; // ���ݿ����

	QYearPlan m_yearPlan; // ��ƻ�
};
