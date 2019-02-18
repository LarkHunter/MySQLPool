#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include<iostream>
#include<thread>
#pragma comment(lib, "ws2_32.lib")  //���� ws2_32.dll

//�����ַ
struct STNetAddress
{
	const char* pszIp;
	int iPort;
	int iSocket;
};
/*---------------------------------------------------------------------------
** ���� : Client
**---------------------------------------------------------------------------
** ���� : �ͻ���
**---------------------------------------------------------------------------
** Date			Name
** 2019.02.11	��ΰ
**---------------------------------------------------------------------------*/
class Client
{
public:

	// ��ʼ��
	Client();

	// �ͷ�
	~Client();

	// �����������
	bool StartNetService();

	// �������
	bool StartNetServiceTest();

	// ��ʼ�㲥
	static void SendBroadCast();
private:

	// ���ӹ��ܷ�����
	int LinkFunctionServer(const char*pszIP, int iPort);
	
	// �ȴ��㲥��Ϣ
	static void BroadCast(int iServerFd);

	// ��ȡ������id
	static int QueryServerSocket();

private:

	static Client* m_pClient; //�ͻ���ָ��

	std::thread* th_BroadCast; //�㲥

	int m_iSubServerSocket; // �������׽���
};

