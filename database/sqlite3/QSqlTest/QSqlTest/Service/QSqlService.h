#pragma once
#include <string>
#include <vector>

typedef std::vector<std::string> VecItemInfo; // �������ݱ�����

/*---------------------------------------------------------------------------
** ���� : QSqlService
**---------------------------------------------------------------------------
** ���� : ���ݿ����
**---------------------------------------------------------------------------
** Date			Name
** 19.04.08		Mark
**---------------------------------------------------------------------------*/
class QSqlService
{
public:
	
	// ��ʼ��
 	QSqlService();

	// ����
	~QSqlService();

public:

	// ��������
	bool StartService(const char* pszDatabase,const char *pszTable );

	// ������Ŀ-
	bool addItem(const char *pszTable,const char*pszItem);
	
	// ɾ����Ŀ
	bool deleteItem(const char *pszTable, int iItemID);

	// �޸�
	bool updateItem(const char *pszTable, const char* pszInfo,int iItemID);

	// �鿴
	bool QueryItemById(const char *pszTable, int iItemId, std::string & strItem);

	// �鿴������Ϣ-
	bool QueryInfo(const char* pszTable, VecItemInfo& vecSumInfo);

private:

	// ��ʼ������
	bool InitDatabase(const char *pszDatabase = "");

	// ��ʼ����
	bool InitTable(const char *pszTable);
};

