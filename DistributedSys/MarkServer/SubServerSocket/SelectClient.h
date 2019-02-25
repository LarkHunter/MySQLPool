#pragma once
#include <winsock2.h>
#include <iostream>
#include "Define/ClientCustomDefine.h"
#include <vector>
#include <map>
#include <thread>
#pragma comment(lib, "ws2_32.lib")  //���� ws2_32.dll

typedef std::vector<int> VecClientFd; // �����Ѿ������ϵĿͻ����׽���������

typedef std::map<int, int > MapClientFd; // ���������ӵĿͻ����׽���������
/*---------------------------------------------------------------------------
** ���� : SubServer
**---------------------------------------------------------------------------
** ���� : �ӷ�����
**---------------------------------------------------------------------------
** Date			Name
** 2018.02.06	Mark
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

	// ������������
	static void OnCustomChat(char*  bufferSend);

	// �ͻ�������Ϣ:��������б�
	static void OnSubCustomList();

	// Ⱥ��
	static void OnSubCustomGroupChat(int iSubMsg,char* pszRecvChat);

	// ��ȡ�����ͻ����׽���
	static int QuerySockClient();

	// ���������ͻ����׽���
	static void SetSocketClient(int iSock_client);

	// ����������Ϣ
	static int ReadClientMsg(char* bufferSend, int &iSubMsg, char* szTxt);
private:

	static SelectClient * m_pSelectClient; // ��ѯ�ͻ�������ģ��

	//VecClientFd m_VecClientFd; // �Ѿ������ϵĿͻ����׽���������

	MapClientFd m_MapClientFd;// �Ѿ������ϵĿͻ����׽���������

	std::thread *m_thSelectClient; // ��ѯ�ͻ��������߳�

	int m_iSock_client;// �ͻ�������

};

