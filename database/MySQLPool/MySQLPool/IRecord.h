#pragma once
#include "ConnPool.h"
#include <string>

// ��¼��
//2019-06-16 Mark
class IRecord
{
public:

	// ����
	IRecord();

	// �ͷ�
	~IRecord();

public:

	// ѡ�����ݿ�
	bool ChooseDatabase(const char* pszDB = "test");

	// ��ȡ���ݱ�
	Statement * GetRecord(const char* spzRecordName);

	// ѡ�����ݱ�
	bool ChooseTable(const char* pszTable);

private:

	const char* m_pszDatabase; // ���ݿ�

	const char* m_pszTable; // ���ݱ� 

	ConnPool *m_connpool; //  ���ݿ����ӳ�
	
	Connection *m_conn; // ���ݿ�����

	Statement *m_state; 


};
