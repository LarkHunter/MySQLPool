#pragma once
#include <winsock2.h>
#include <iostream>
#include <vector>
#include <thread>
#pragma comment(lib, "ws2_32.lib")  //���� ws2_32.dll

typedef std::vector<int> VecClientFd; // �����Ѿ������ϵĿͻ����׽���������

/*---------------------------------------------------------------------------
** ���� : SubServer
**---------------------------------------------------------------------------
** ���� : �ӷ�����
**---------------------------------------------------------------------------
** Date			Name
** 2018.02.06	��ΰ
**---------------------------------------------------------------------------*/
class SelectClient
{
public:

	// ��ʼ��
	SelectClient();

	// �ͷ�
	~SelectClient();

	// ��ʼ���������
	bool InitNetService();

private:

	// ��ʼ���׽���
	int InitSocket();

	// ����ͻ�������
	bool DealNetRequest(int iServerfd);

private:

	VecClientFd m_VecClientFd; // �Ѿ������ϵĿͻ����׽���������

};

