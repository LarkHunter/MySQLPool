#pragma once
#include "ConnPool.h"
#include <string>

// 记录表
//2019-06-16 Mark
class IRecord
{
public:

	// 构造
	IRecord();

	// 释放
	~IRecord();

public:

	// 选择数据库
	bool ChooseDatabase(const char* pszDB = "test");

	// 获取数据表
	Statement * GetRecord(const char* spzRecordName);

	// 选择数据表
	bool ChooseTable(const char* pszTable);

private:

	const char* m_pszDatabase; // 数据库

	const char* m_pszTable; // 数据表 

	ConnPool *m_connpool; //  数据库连接池
	
	Connection *m_conn; // 数据库连接

	Statement *m_state; 


};
