#pragma once
#include <QString>
#include "DataOpration/DataOperation.h"

/*---------------------------------------------------------------------------
** ���� : FileOpration
**---------------------------------------------------------------------------
** ���� : �ļ����ݲ���
**---------------------------------------------------------------------------
** Date			Name
** 2019.04.01	Mark
**---------------------------------------------------------------------------*/
class FileOpration
{
public:
	
	// ���캯��
	FileOpration();

	// ��������
	~FileOpration();

public:

	// ����Ҫ�������Ŀ
	static bool addPlanItem(const char* pszFile, QString& qstrPlan);

	// ���ɾ����Ŀ֮�󣬸����ļ�
	static bool UpdatePlanFile(const char* pszFile, MapItemPlan& mapItemPlan);
private:

};

