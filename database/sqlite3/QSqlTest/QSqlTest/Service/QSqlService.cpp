#include "QSqlService.h"
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QVariantList>
#include <QDebug>

/*---------------------------------------------------------------------------
** ���� : QSqlService
** ���� : ��ʼ��
**---------------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**---------------------------------------------------------------------------
** Date			Name
** 19.04.08		��ΰ
**---------------------------------------------------------------------------*/
QSqlService::QSqlService()
{

}

/*---------------------------------------------------------------------------
** ���� : ~QSqlService
** ���� : ��ʼ��
**---------------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**---------------------------------------------------------------------------
** Date			Name
** 19.04.08		��ΰ
**---------------------------------------------------------------------------*/
QSqlService::~QSqlService()
{

}
/*---------------------------------------------------------------------------
** ���� : StartService
** ���� : ��������
**---------------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**---------------------------------------------------------------------------
** Date			Name
** 19.04.08		��ΰ
**---------------------------------------------------------------------------*/
bool QSqlService::StartService(const char* pszDatabase, const char *pszTable)
{
	if( (!pszDatabase) ||
		(!pszTable) )
	{

	}

	bool bResult = InitDatabase(pszDatabase); // ��ʼ�����ݿ�
	if (!bResult)
	{
		return bResult;
	}

	bResult = InitTable(pszTable); // ��ʼ����
	if(!bResult)
	{
		return bResult;
	}

	return true;
}
/*---------------------------------------------------------------------------
** ���� : addItem
** ���� : ������Ŀ
**---------------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**---------------------------------------------------------------------------
** Date			Name
** 19.04.08		��ΰ
**---------------------------------------------------------------------------*/
bool QSqlService::addItem(const char *pszTable,const char*pszItem)
{
	if( (!pszTable)|| 
		(!pszItem) )
	{
		return false;
	}

	std::string strQuerySQl("select count(*) as value from");
	strQuerySQl.append(" ");
	strQuerySQl.append(pszTable);

	const char* pszQuerySql = strQuerySQl.c_str();

	QSqlQuery query;

	query.exec(pszQuerySql);

	int iCount = 0;
	while(query.next())
	{
		qDebug() << query.value(0).toInt();
		iCount = query.value(0).toInt();

	}
	//int iCount = query.value(0).toInt();
	iCount += 1;

	std::string strInsert("insert into");
	strInsert.append(" ");
	strInsert.append(pszTable);
	strInsert.append(" ");
	strInsert.append("values (");
	strInsert.append(std::to_string(iCount));
	strInsert.append(",");
	strInsert.append("'");
	strInsert.append(pszItem);
	strInsert.append("'");
	strInsert.append(")");

	const char* pszInsert = strInsert.c_str();
	bool bResult = query.exec(pszInsert);

	return bResult;
}
/*---------------------------------------------------------------------------
** ���� : deleteItem
** ���� : ɾ����Ŀ
**---------------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**---------------------------------------------------------------------------
** Date			Name
** 19.04.08		��ΰ
**---------------------------------------------------------------------------*/
bool QSqlService::deleteItem(const char *pszTable, int iItemID)
{
	if(!pszTable)
	{
		return false;
	}
	if(iItemID <0)
	{
		return false;
	}

	std::string strDeleteSQl("delete from");
	strDeleteSQl.append(" ");
	strDeleteSQl.append(pszTable);
	strDeleteSQl.append(" ");
	strDeleteSQl.append("where id = ");
	strDeleteSQl.append(std::to_string(iItemID));

	const char* pszDeleteSQL = strDeleteSQl.c_str();

	QSqlQuery query;
	bool bResult = query.exec(pszDeleteSQL);

	return bResult;

}
/*---------------------------------------------------------------------------
** ���� : updateItem
** ���� : ������Ŀ
**---------------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**---------------------------------------------------------------------------
** Date			Name
** 19.04.08		��ΰ
**---------------------------------------------------------------------------*/
bool QSqlService::updateItem(const char *pszTable, const char* pszInfo, int iItemID)
{
	if( (!pszTable) ||
		(!pszInfo) )
	{
		return false;
	}

	if(iItemID < 0)
	{
		return false;
	}

	std::string strUpdateSQL("update");
	strUpdateSQL.append(" ");
	strUpdateSQL.append(pszTable);
	strUpdateSQL.append("set info=");
	strUpdateSQL.append(pszInfo);
	strUpdateSQL.append("where id = ");
	strUpdateSQL.append(std::to_string(iItemID));

	const char* pszUpdateSQl = strUpdateSQL.c_str();
	QSqlQuery query;
	bool bResult = query.exec(pszUpdateSQl);

	return bResult;

}
/*---------------------------------------------------------------------------
** ���� : QueryItemById
** ���� : �鿴ĳID��Ϣ
**---------------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**---------------------------------------------------------------------------
** Date			Name
** 19.04.09		Mark
**---------------------------------------------------------------------------*/
bool QSqlService::QueryItemById(const char *pszTable, int iItemId, std::string & strItem)
{
	if(!pszTable)
	{
		return false;
	}

	if(iItemId <0)
	{
		return false;
	}

	std::string strQuerySQl("select info from ");
	strQuerySQl.append(" ");
	strQuerySQl.append(pszTable);
	strQuerySQl.append("where id = ");
	strQuerySQl.append(std::to_string(iItemId));

	QSqlQuery query;

	const char* pszQuerySql = strQuerySQl.c_str();
	bool bResult = query.exec(pszQuerySql);

	while(query.next())
	{
		//ȡ����ǰ�е�����
		qDebug() << query.value(0).toInt()
			<< query.value(1).toString();
		
		strItem = query.value(1).toString().toStdString();
	}
	return true;
}
/*---------------------------------------------------------------------------
** ���� : QueryInfo
** ���� : �鿴��ǰ��������Ϣ
**---------------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**---------------------------------------------------------------------------
** Date			Name
** 19.04.09		Mark
**---------------------------------------------------------------------------*/
bool QSqlService::QueryInfo(const char* pszTable, VecItemInfo& vecSumInfo)
{
	if(!pszTable)
	{
		return false;
	}

	std::string strQueryInfoSum("select info from");
	strQueryInfoSum.append(" ");
	strQueryInfoSum.append(pszTable);

	const char* pszQueryInfoSum = strQueryInfoSum.c_str();

	QSqlQuery query;
	bool bResult = query.exec(pszQueryInfoSum);
	while(query.next())
	{
		std::string strItem = query.value(0).toString().toStdString();
		vecSumInfo.push_back(strItem);
	}

	return true;
}

/*---------------------------------------------------------------------------
** ���� : InitService
** ���� : ��ʼ������
**---------------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**---------------------------------------------------------------------------
** Date			Name
** 19.04.08		Mark
**---------------------------------------------------------------------------*/
bool QSqlService::InitDatabase(const char *pszDatabase /*= ""*/)
{
	if(!pszDatabase)
	{
		return false;
	}

	//��ӡQt֧�ֵ����ݿ�����
	qDebug() << QSqlDatabase::drivers();

	//���Sqlite���ݿ�
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

	//�������ݿ�
	db.setDatabaseName("../info.db");

	//�����ݿ�
	if (!db.open())
	{
		qDebug() << "database open error";
		//QMessageBox::warning(this, "error", db.lastError().text());
		return false;
	}

	return true;
}

/*---------------------------------------------------------------------------
** ���� : InitTable
** ���� : ��ʼ����
**---------------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**---------------------------------------------------------------------------
** Date			Name
** 19.04.08		��ΰ
**---------------------------------------------------------------------------*/
bool QSqlService::InitTable(const char *pszTable)
{
	if(!pszTable)
	{
		return false;
	}
	std::string strSQl("create table if not exists");
	strSQl.append(" ");
	strSQl.append(pszTable);
	strSQl.append("(id int PRIMARY KEY AUTOINCREMENT , info varchar(255)");
	strSQl.append(")");
	const char*pszSQl = strSQl.c_str();

	QSqlQuery query;
	bool bResult = query.exec(pszSQl);
	//query.exec("select * from test");
	// 	query.prepare("insert into student(id,name, age, score) values(:id,:name, :age, :score)");
	// 
	// 	//���ֶ��������� list
	// 	QVariantList idList;
	// 	idList << 1 << 2 << 3;
	// 
	// 	QVariantList nameList;
	// 	nameList << "xiaoming" << "xiaolong" << "xiaojiang";
	// 
	// 	QVariantList ageList;
	// 	ageList << 11 << 22 << 33;
	// 
	// 	QVariantList scoreList;
	// 	scoreList << 59 << 69 << 70;
	// 
	// 	//���ֶΰ���Ӧ��ֵ ��˳���
	// 	query.addBindValue(idList);
	// 
	// 	query.addBindValue(nameList);
	// 
	// 	query.addBindValue(ageList);
	// 
	// 	query.addBindValue(scoreList);

	//ִ��Ԥ��������
	//bool bResult = query.exec();

	return bResult;
}
