#include "SelectClientSocket.h"


/*--------------------------------------------------------------------
** ���� : SelectClientSocket
**--------------------------------------------------------------------
** ���� : ��ʼ��
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.12		��ΰ
**-------------------------------------------------------------------*/
SelectClientSocket::SelectClientSocket()
{

}

/*--------------------------------------------------------------------
** ���� : ~SelectClientSocket
**--------------------------------------------------------------------
** ���� : �ͷ�
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.12		��ΰ
**-------------------------------------------------------------------*/
SelectClientSocket::~SelectClientSocket()
{

}
/*--------------------------------------------------------------------
** ���� : InitNetService
**--------------------------------------------------------------------
** ���� : ��ʼ���������
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.10		��ΰ
**-------------------------------------------------------------------*/
bool SelectClientSocket::InitNetService()
{

}

/*--------------------------------------------------------------------
** ���� : InitSocket
**--------------------------------------------------------------------
** ���� : ��ʼ������
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : serverfd
**--------------------------------------------------------------------
** Date:		Name
** 19.02.12		��ΰ
**-------------------------------------------------------------------*/
int SelectClientSocket::InitSocket()
{
	//��ʼ��DLL
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (NO_ERROR != iResult)
	{
		return 0;
	}

	//�����׽���
	SOCKET iListenSocket = INVALID_SOCKET;
	iListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == iListenSocket)
	{
		std::cout << "Create Socket Error!" << std::endl;

		WSACleanup();

		return 0;
	}
	else
	{
		std::cout << "Create Socket Success" << std::endl;
	}

	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(27000);

	//----------------------
	// Bind the socket.
	iResult = bind(iListenSocket, (SOCKADDR *)&service, sizeof(service));
	if (INVALID_SOCKET == iResult)
	{
		WSACleanup();

		return 0;
	}
	else
	{
		std::cout << "Bind Socket Success" << std::endl;
	}

	int iRet = listen(iListenSocket, SOMAXCONN);
	if (0 != iRet)
	{
		return 0;
	}
	else
	{
		std::cout << "Listen Socket Success" << std::endl;
	}

	return iListenSocket;
}
