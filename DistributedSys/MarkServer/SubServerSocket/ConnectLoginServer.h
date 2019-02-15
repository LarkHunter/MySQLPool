#pragma once
#include <thread>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")  //���� ws2_32.dll

#include <iostream>
using namespace std;
/*---------------------------------------------------------------------------
** ���� : ConnectLoginServer
**---------------------------------------------------------------------------
** ���� : ��������
**---------------------------------------------------------------------------
** Date			Name
** 2018.02.06	��ΰ
**---------------------------------------------------------------------------*/
class ConnectLoginServer
{
public:

	// ��ʼ��
	ConnectLoginServer();

	// �ͷ�
	~ConnectLoginServer();
public:

	// �����������
	bool StartNetService();
private:

	// �����׽���
	int CreateSocket();

	// ������������
	bool ConnectMainServer(int iListenSocket);

	// �������߳�
	//void SubHeart();
private:
	std::thread *th_heartToLoginServer;
};