#ifndef D_CONNECTION_POOL_H
#define D_CONNECTION_POOL_H

#include "include/mysql/jdbc.h"
#include "mysql-connector-c++/release/mysql-connector-c++-8.0.16-winx64/include/mysql/jdbc.h"
#include<mutex>
#include <list>

#ifdef _WIN64
#pragma comment(lib,"mysql-connector-c++/debug/mysql-connector-c++-8.0.16-winx64/lib64/vs14/debug/mysqlcppconn.lib")
#else
#pragma comment(lib,"mysql-connector-c++/debug/mysql-connector-c++-8.0.16-win32/lib/vs14/debug/mysqlcppconn.lib")

#endif // WIN64

using namespace std;
using namespace sql;

typedef std::list<Connection*> LConnList; // ��������

// ���ݿ����ӳ�
// 2019-06-16 Mark
class ConnPool
{
public:

	// �ͷ�������Դ
	~ConnPool();

	// ��ȡ���Ӷ���
	static ConnPool *GetConnInstance();

	// ��ʼ�����ӳ�
	static void InitConnection(int iConnectNum);

	// ��ȡ���ݿ�����
	Connection *GetConnection();

	// �黹����
	void BackConnection(sql::Connection * conn);

private:

	// �������ӳ�
	ConnPool(const char* pszUrl = "", const char* pszUser ="", const char* pszPwd = "", int iMaxSize = 0);

	// �������ļ���ʼ�����Ӷ���
	static void InitConnPoolByCfg();

	// ����һ������
	static Connection* CreateConnection();

	// �ر�һ�����ݿ�����
	void CloseAConnection(Connection* conn);

	// �������ݿ����ӳ�
	void DestoryConnPool();

public:
	static ConnPool* m_pConnPoolModule; // ���ӳ�ģ��

private:

	static ConnPool* m_connPoolIntance; // ���ݿ����ӳض���

	std::string m_strDBUrl; // ���ݿ�����URL

	std::string m_strDBUser; // ���ݿ������û���

	std::string m_strDBPwd; // ���ݿ�����

	int m_iDBPoolMaxSize; // ���ݿ����ӳ������������

	Driver* m_driver; // ��������

	std::mutex m_mutex; // ������

	LConnList m_lConnList; // ���Ӷ���


};


#endif
