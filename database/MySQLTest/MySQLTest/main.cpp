#include <iostream>
#include <windows.h>
#include "MySQlConn.h"
#include "DatabaseDefine.h"

int main()
{
	MySQlConn m_MySQlConn;

	// ��ʼ�����ݿ�
 	bool bResult = m_MySQlConn.Init();
 	if(!bResult)
 	{
 		return 0;
 	}
 
	

	VecField vecField;
	STField stField;

	stField.strSTFieldName = "��ԱID";
	stField.strSTFieldType = D_INT;
	vecField.push_back(stField);
	stField.Clear();
	
	stField.strSTFieldName = "��Ա����";
	stField.strSTFieldType = D_VARCHAR;
	vecField.push_back(stField);
	stField.Clear();

	stField.strSTFieldName = "����";
	stField.strSTFieldType = D_VARCHAR;
	vecField.push_back(stField);
	stField.Clear();

	stField.strSTFieldName = "����";
	stField.strSTFieldType = D_INT;
	vecField.push_back(stField);
	stField.Clear();

	// ������
	m_MySQlConn.CreateTable("ŷ�ޱ�", vecField);

	// ѡ���
// 	bResult = m_MySQlConn.SelectTable(D_LOCAL_TABLE);
// 	if(!bResult)
// 	{
// 		return 0;
// 	}

	// ����ֵ 
// 	m_MySQlConn.setString("INZAGHI");
// 	if (!bResult)
// 	{
// 		return 0;
// 	}

	// ɾ��ֵ
// 	bResult = m_MySQlConn.deleteValue(7); // �д�
// 	if(!bResult)
// 	{
// 		return 0;
// 	}

	std::cout <<"...." << std::endl;
	system("pause");
	return 0;
}