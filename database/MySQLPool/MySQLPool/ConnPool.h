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

typedef std::list<Connection*> LConnList; // 连接链表

// 数据库连接池
// 2019-06-16 Mark
class ConnPool
{
public:

	// 释放连接资源
	~ConnPool();

	// 获取连接对象
	static ConnPool *GetConnInstance();

	// 初始化连接池
	static void InitConnection(int iConnectNum);

	// 获取数据库连接
	Connection *GetConnection();

	// 归还连接
	void BackConnection(sql::Connection * conn);

private:

	// 构造连接池
	ConnPool(const char* pszUrl = "", const char* pszUser ="", const char* pszPwd = "", int iMaxSize = 0);

	// 由配置文件初始化连接对象
	static void InitConnPoolByCfg();

	// 创建一个连接
	static Connection* CreateConnection();

	// 关闭一个数据库连接
	void CloseAConnection(Connection* conn);

	// 销毁数据库连接池
	void DestoryConnPool();

public:
	static ConnPool* m_pConnPoolModule; // 连接池模块

private:

	static ConnPool* m_connPoolIntance; // 数据库连接池对象

	std::string m_strDBUrl; // 数据库连接URL

	std::string m_strDBUser; // 数据库连接用户名

	std::string m_strDBPwd; // 数据库密码

	int m_iDBPoolMaxSize; // 数据库连接池最大连接数量

	Driver* m_driver; // 连接驱动

	std::mutex m_mutex; // 互斥锁

	LConnList m_lConnList; // 连接队列


};


#endif
