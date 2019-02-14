#pragma once
#include <vector>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <thread>

#pragma comment(lib, "ws2_32.lib")  //���� ws2_32.dll

typedef std::vector<SOCKET> VecSubServerSocket; // �ӷ������׽���

/*---------------------------------------------------------------------------
** ���� : AceptServerSocket
**---------------------------------------------------------------------------
** ���� : �����ܷ���������
**---------------------------------------------------------------------------
** Date			Name
** 2018.01.31	��ΰ
**---------------------------------------------------------------------------*/
class AcceptServerSocket
{
public:

	// ��ʼ��
	AcceptServerSocket();

	// �ͷ�
	~AcceptServerSocket();

public:

	// �����������
	bool StartNetService();

	// ��ȡ�����ӷ�����
	static bool QueryOnlineSubServer(VecSubServerSocket& vecSubServerSocket);

private:

	// �����׽���
	int CreateSocket();

	// ���׽���
	bool BindSocket(int iListenSocket);

	// �����׽���
	bool ListenSocket(int iListenSocket);

	// ���ܿͻ�������
	bool AcceptSocket(int iListenSocket);

	// ������߳�����
	static void DetectSubServerHeart();

	// �����ӷ���������
	static void AcceptSubServerConnect(int iListenSocket);

	// ����ӷ�����
	static void DetectSubServer();

	// ����ӷ�������������
	static void DetectSubServerConnect(int iAcceptSocket);

	// ���书�ܷ�����
	static int DistributeServerSocket();


private:
	static AcceptServerSocket* m_pAcceptServerSocket;

	VecSubServerSocket m_vecSubServerSocket; // �ӷ������������׽���
};
