#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")  //���� ws2_32.dll

#include <iostream>
using namespace std;
/*---------------------------------------------------------------------------
** ���� : SubServer
**---------------------------------------------------------------------------
** ���� : ��������
**---------------------------------------------------------------------------
** Date			Name
** 2018.02.06	��ΰ
**---------------------------------------------------------------------------*/
class SubServer
{
public:

	// ��ʼ��
	SubServer();

	// �ͷ�
	~SubServer();
public:

	// �����������
	bool StartSubServer();
private:

	// �����׽���
	int CreateSocket();

	// ������������
	bool ConnectMainServer(int iListenSocket);

	// �������߳�
	//void SubHeart();

};