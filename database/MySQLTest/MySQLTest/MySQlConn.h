#pragma once
#include "winsock.h" 
#include "include/mysql.h" 
#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>

#pragma comment(lib,"libmySQL.lib") 

// ���ֶ�
struct STField
{
	std::string strSTFieldType;
	std::string strSTFieldName;

	STField() :strSTFieldType(""), strSTFieldName("")
	{

	}

	bool Clear()
	{
		strSTFieldType.clear();
		strSTFieldName.clear();

		return true;
	};
};

typedef std::vector<std::string> VecDatabase;

typedef std::vector<STField> VecField; // �ֶ�

typedef std::map<int, std::string > MapInfo; // ��ѯ���
/*---------------------------------------------------------------------------
** ���� : MySQlConn
**---------------------------------------------------------------------------
** ���� : MySQL���ݿ����
**---------------------------------------------------------------------------
** Date			Name
** 19.04.10		��ΰ
**---------------------------------------------------------------------------*/
class MySQlConn
{

public:

	// �������ݿ�
	MySQlConn();

	// �������ݿ�
	~MySQlConn();
public:

	// ��ʼ�����ݿ�
	bool Init(const char* pszIp = "127.0.0.1", const char*pszAccount = "root",const char* pszPwd = "123456",
		const char*pszDB = "test", const char *unix_socket = NULL);

	// �������ݿ�
	bool CreateDatabase(const char* pszDatabase);

	// �鿴���ݿ�
	bool ShowDatabase(VecDatabase& vecDatabase);

	// ������
	bool CreateTable(const char* pszTable,VecField& vecField);

	// ʹ�����ݱ�
	bool SelectTable(const char* pszTable);

	// ��
	bool setString(const char* pszItem);

	// ɾ��
	bool deleteValue(int iID);

	// ��
	bool modifyValue(int iID, const char*pszValue);

	//��
	//bool queryValue(int iID,std::string& strValue);

	// ��ѯȫ����Ϣ
	//bool queryAllValue(MapInfo & mapInfo);

public:

	MYSQL *m_mysql; // ���ݿ����
	
	const char* m_pszTable; // ��ǰ��
};

