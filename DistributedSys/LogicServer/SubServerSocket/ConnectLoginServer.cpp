#include "ConnectLoginServer.h"
#include <windows.h>

/*--------------------------------------------------------------------
** ���� : SubHeart
**--------------------------------------------------------------------
** ���� : ���߳���������ʱ����������
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.06		��ΰ
**-------------------------------------------------------------------*/
void SubHeart(int iListenSocket)
{
	const char *buf = "Alived";
	while(1)
	{
		cout <<"buf = " << buf << "sizeof(buf)!"<< strlen(buf) <<endl;
		send(iListenSocket,buf, strlen(buf),0);

		Sleep(5000);
	}
}

/*--------------------------------------------------------------------
** ���� : SubServer
**--------------------------------------------------------------------
** ���� : ��ʼ��
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.06		��ΰ
**-------------------------------------------------------------------*/
ConnectLoginServer::ConnectLoginServer()
{

}
/*--------------------------------------------------------------------
** ���� : ~ConnectLoginServer
**--------------------------------------------------------------------
** ���� : �ͷ�
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.06		��ΰ
**-------------------------------------------------------------------*/
ConnectLoginServer::~ConnectLoginServer()
{
	delete th_heartToLoginServer;
}
/*--------------------------------------------------------------------
** ���� : StartConnectLoginServer
**--------------------------------------------------------------------
** ���� : �����������
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.06		��ΰ
**-------------------------------------------------------------------*/
bool ConnectLoginServer::StartNetService()
{ 
	int iSocket = CreateSocket();
	if(0 == iSocket)
	{
		std::cout <<"To LoginServer: CreateSocket Falied " <<std::endl;

		return false;
	}

	bool bResult = ConnectMainServer(iSocket);
	
	return bResult;

}
/*--------------------------------------------------------------------
** ���� : CreateSocket
**--------------------------------------------------------------------
** ���� : �����׽���
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.06		��ΰ
**-------------------------------------------------------------------*/
int ConnectLoginServer::CreateSocket()
{
	//��ʼ��DLL
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if(NO_ERROR != iResult)
	{
		return 0;
	}

	//�����׽���
	SOCKET ListenSocket = INVALID_SOCKET;
	ListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(INVALID_SOCKET == ListenSocket)
	{
		std::cout << "Create Socket Error!" << std::endl;

		WSACleanup();

		return 0;
	}
	else
	{
		std::cout << "Create Socket Success" << std::endl;
	}

	return ListenSocket;

}
/*--------------------------------------------------------------------
** ���� : ConnectMainServer
**--------------------------------------------------------------------
** ���� : ������������
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.06		��ΰ
**-------------------------------------------------------------------*/
bool ConnectLoginServer::ConnectMainServer(int iListenSocket)
{
	sockaddr_in service;

	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(27015);

	//----------------------
	// Bind the socket.
	int iResult = connect(iListenSocket, (SOCKADDR *)&service, sizeof(service));
	if(0 != iResult)
	{
		std::cout <<"To LoginServer:  ConnectMainServer Failed " << iResult << std::endl;
	}
	else
	{
		std::cout << "To LoginServer: ConnectMainServer Success!" << std::endl;

		// ��������
		th_heartToLoginServer = new std::thread(SubHeart, iListenSocket);
		
	}

	return true;
}


