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

	// ��Ӧ�ͻ�������
	static bool th_DealClientConnect(int iServerfd);

	// ����㲥
	static void DealBroadCast(char*  bufferSend);

	// ��ȡ�����ͻ����׽���
	static int QuerySockClient();

	// ���������ͻ����׽���
	static void SetSocketClient(int iSock_client);
private:

	static SelectClient * m_pSelectClient; // ��ѯ�ͻ�������ģ��

	VecClientFd m_VecClientFd; // �Ѿ������ϵĿͻ����׽���������

	std::thread *m_thSelectClient; // ��ѯ�ͻ��������߳�

	int m_iSock_client;// �ͻ�������

};

