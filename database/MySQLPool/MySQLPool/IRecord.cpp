#include "IRecord.h"

IRecord::IRecord()
{
	// 获取数据库连接池对象
	try
	{
		m_connpool = ConnPool::GetConnInstance();
	}
	catch(...)
	{
		cout <<"IRecord Construt Connpool Error " << endl;

		return;
	}
	
	// 初始化一定数量的连接
	ConnPool::InitConnection(10);

	// 从连接池中取出一条连接
	try
 	{
 		m_conn = m_connpool->GetConnection(); 

 	}
 	catch (...)
 	{
		 cout << "IRecord Construt Connpool Error " << endl;

		 return;
 	}
	
	try
	{
		m_state = m_conn->createStatement();
	}
	catch (...)
	{
		cout << "IRecord Construt State Error " << endl;

		return;
	}
	
}

IRecord::~IRecord()
{

}

// 选择数据库
bool IRecord::ChooseDatabase(const char* pszDB /*= "test"*/)
{
	if(NULL == pszDB)
	{
		return false;
	}

	std::string strStateSQl("use");
	strStateSQl.append(" ");
	strStateSQl.append(pszDB);

	const char* pszStateDb = strStateSQl.c_str();

	try
	{
		m_state->execute(pszStateDb);
	}
	catch(...)
	{
		cout << "Use Database " << pszDB<< " Failed !"<< endl;

		return false;
	}

	return true;
}

// 获取数据表
Statement * IRecord::GetRecord(const char* spzRecordName)
{
	m_pszTable = m_pszDatabase;

	return m_state;
}

// 选择数据表
bool IRecord::ChooseTable(const char* pszTable)
{
	if(NULL == pszTable)
	{
		return false;
	}

	return true;
}
