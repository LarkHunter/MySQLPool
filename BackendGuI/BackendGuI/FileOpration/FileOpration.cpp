#include "FileOpration.h"
#include <QFile>
#include <QDebug>
/*--------------------------------------------------------------------
** ���� : FileOpration
**--------------------------------------------------------------------
** ���� : ���캯��
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.04.1		Mark
**-------------------------------------------------------------------*/
FileOpration::FileOpration()
{

}
/*--------------------------------------------------------------------
** ���� : ~FileOpration
**--------------------------------------------------------------------
** ���� : ��������
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.04.1		Mark
**-------------------------------------------------------------------*/
FileOpration::~FileOpration()
{

}

/*--------------------------------------------------------------------
** ���� : addPlanItem
**--------------------------------------------------------------------
** ���� : ���������ļƻ�
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.04.1		Mark
**-------------------------------------------------------------------*/
bool FileOpration::addPlanItem(const char* pszFile, QString& qstrPlan)
{
	if(!pszFile ||
		qstrPlan.isNull())
	{
		return false;
	}

	// ���浽�ļ���
	QFile fileout(pszFile);

	if(!fileout.open(QIODevice::Append | QIODevice::Text))
	{
		qDebug() << "Open failed";
		return false;
	}

	qstrPlan.append("\n");
	std::string strPlan = qstrPlan.toStdString();
	const char* pszPlan = strPlan.c_str();

	fileout.write(pszPlan);

	return true;
}
/*--------------------------------------------------------------------
** ���� : UpdatePlanFile
**--------------------------------------------------------------------
** ���� : ɾ���ƻ�֮�󣬸����ļ�
**--------------------------------------------------------------------
** ���� : pszFile �ļ��� 
** ���� : mapItemPlan �ƻ�������
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.04.1		Mark
**-------------------------------------------------------------------*/
bool FileOpration::UpdatePlanFile(const char* pszFile, MapItemPlan& mapItemPlan)
{
	if(!pszFile)
	{
		return false;
	}

// 	int iSize = mapItemPlan.size();
// 	if(iSize <=0)
// 	{
// 		return false;
// 	}

	QFile oldfile(pszFile);

	oldfile.remove(); // ɾ��֮ǰ���ļ�

	QFile file(pszFile);
	//	file.setFileName(D_YEAR_PLAN);
	if(!file.exists())
	{
		if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
		{
			return false;
		}
	}
	else
	{
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			return false;
		}
	}

	MapItemPlan::iterator itMap = mapItemPlan.begin();
	int iKey = 1;

	for(; itMap!= mapItemPlan.end(); itMap++)
	{
		
		QString qstrPlan = itMap->second;

		QString qstrKeyAndPlan;
		qstrKeyAndPlan = QString::number(iKey);
		qstrKeyAndPlan.append(":");
		qstrKeyAndPlan.append(qstrPlan);

		addPlanItem(pszFile, qstrKeyAndPlan);

		iKey += 1;
	}
	
	return true;
}
