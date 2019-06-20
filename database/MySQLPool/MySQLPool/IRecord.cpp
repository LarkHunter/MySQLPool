#include "IRecord.h"

IRecord::IRecord()
{
	// ��ȡ���ݿ����ӳض���
	try
	{
		m_connpool = ConnPool::GetConnInstance();
	}
	catch(...)
	{
		cout <<"IRecord Construt Connpool Error " << endl;

		return;
	}
	
	// ��ʼ��һ������������
	ConnPool::InitConnection(10);

	// �����ӳ���ȡ��һ������
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

// ѡ�����ݿ�
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

// ��ȡ���ݱ�
Statement * IRecord::GetRecord(const char* spzRecordName)
{
	m_pszTable = m_pszDatabase;

	return m_state;
}

// ѡ�����ݱ�
bool IRecord::ChooseTable(const char* pszTable)
{
	if(NULL == pszTable)
	{
		return false;
	}

	return true;
}
