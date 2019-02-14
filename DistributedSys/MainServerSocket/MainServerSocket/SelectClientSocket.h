#pragma once
#include <winsock2.h>
#include <iostream>
#include <vector>
#pragma comment(lib, "ws2_32.lib")  //���� ws2_32.dll

typedef std::vector<int> VecClientFd; // �����Ѿ������ϵĿͻ����׽���������

/*---------------------------------------------------------------------------
** ���� : SelectClientSocket
**---------------------------------------------------------------------------
** ���� : ��¼��������ѯ�ͻ�������
**---------------------------------------------------------------------------
** Date			Name
** 2019.02.12	��ΰ
**---------------------------------------------------------------------------*/
class SelectClientSocket
{
public:
	
	// ��ʼ��
	SelectClientSocket();

	// �ͷ�
	~SelectClientSocket();
public:

	// ��ʼ���������
	bool StartNetService();

private:

	// ��ʼ���׽���
	int InitSocket();

	// ��ѯ�ͻ�������
	bool SelectCilentConnect(int iSeverSocketfd);

	// �����ӷ�����
	int AllocateSubServer();
private:
	
	VecClientFd m_vecClientFd; // �ͻ�������
	
};

