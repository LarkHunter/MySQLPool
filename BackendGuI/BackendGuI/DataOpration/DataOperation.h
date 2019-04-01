#pragma once
#include <map>
#include <QString>
#include <QFile>
#include <QtCore/QTextStream>

typedef std::map<int, QString> MapItemPlan;
/*---------------------------------------------------------------------------
** ���� : DataOperation
**---------------------------------------------------------------------------
** ���� : ���������ݲ���
**---------------------------------------------------------------------------
** Date			Name
** 2019.04.01	Mark
**---------------------------------------------------------------------------*/
class DataOperation
{
public:
	// ���캯�� 
	DataOperation();

	// ��������
	~DataOperation();

public:

	// �����ƻ�
	static bool addPlan(MapItemPlan& mapPlan,int iKey,QString &qstrPlan);

	// ɾ���ƻ�
	static bool deletePlan(MapItemPlan& mapPlan, int iKey);

	// �޸ļƻ�
	static bool modifyPlan(MapItemPlan& mapPlan, int iKey, QString &qstrPlan);

	// �жϵ�ǰ�ƻ��Ƿ����
	static bool isPlanExist(MapItemPlan& mapPlan, int iKey);

	// �����ƻ�����ȡKey
	static int QueryPlanKey(MapItemPlan& mapPlan);

	// ���¼ƻ�
	static bool renewPlanItem(const char* pszPlanFile,MapItemPlan& mapPlan);

private:
	
	// ���µ������еļƻ�
	static void renewPlanMap(QString& qstrInfo, MapItemPlan& mapPlan);
};