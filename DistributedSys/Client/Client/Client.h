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
private:

	// ���ӹ��ܷ�����
	int LinkFunctionServer(const char*pszIP, int iPort);
	
	// �ȴ��㲥��Ϣ
	static void BroadCast(int iServerFd);

private:
	std::thread* th_BroadCast; //�㲥
};

