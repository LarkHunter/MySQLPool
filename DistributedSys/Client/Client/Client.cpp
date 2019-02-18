#include "Client.h"
#define DEFAULT_BUFLEN 256


/*--------------------------------------------------------------------
** ���� : Client
**--------------------------------------------------------------------
** ���� : ��ʼ��
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.11		��ΰ
**-------------------------------------------------------------------*/
Client::Client()
{
}

/*--------------------------------------------------------------------
** ���� : ~Client
**--------------------------------------------------------------------
** ���� : �ͷ�
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.11		��ΰ
**-------------------------------------------------------------------*/
Client::~Client()
{
	delete th_BroadCast;
}

/*--------------------------------------------------------------------
** ���� : StartNetService
**--------------------------------------------------------------------
** ���� : �����������
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.11		��ΰ
**-------------------------------------------------------------------*/
bool Client::StartNetService()
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

	if(INVALID_SOCKET == iListenSocket)
	{
		std::cout << "Create Socket Error!" << std::endl;

		WSACleanup();

		return false;
	}
	else
	{
		std::cout << "Create Socket Success" << std::endl;
	}

	sockaddr_in service;

	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(6666);

	//----------------------
	// Bind the socket.
	iResult = connect(iListenSocket, (SOCKADDR *)&service, sizeof(service));
	if (0 != iResult)
	{
		std::cout << "ConnectMainServer Failed " << iResult << std::endl;
	}
	else
	{
		std::cout << "ConnectMainServer Success!" << std::endl;
		//const char *buf = "OK";
		//send(iListenSocket, buf, strlen(buf), 0);
		char recvbuf[DEFAULT_BUFLEN];
		int recvbuflen = DEFAULT_BUFLEN;

		iResult = recv(iListenSocket, recvbuf, recvbuflen, 0);
		if(iResult > 0)
		{
			std::cout << "  recvbuf= " << recvbuf << std::endl;
			printf("recvbuf = %s\n", recvbuf);

			int iMarkSocket = LinkFunctionServer("127.0.0.1",9999);
			if(iMarkSocket > 0)
			{
				//th_BroadCast = new std::thread(BroadCast,static_cast<int>(iMarkSocket)); //�����㲥

				const char*pszBuffer = "OK BroadCase";
				send(iMarkSocket,pszBuffer,sizeof(pszBuffer),0);

				char recvbuf[DEFAULT_BUFLEN];
				int recvbuflen = DEFAULT_BUFLEN;

				int iResult = recv(iMarkSocket, recvbuf, recvbuflen, 0);
				if(iResult >0)
				{
					std::cout <<"ok recvbuf = "<< recvbuf << std::endl;
				}
				else
				{
					std::cout <<"..." << std::endl;
				}
			}
		}
		else if(0 == iResult)
		{
			std::cout <<"Connection Closed!" << std::endl;
		}
		else
		{
			std::cout << "Received Error"<< WSAGetLastError()<< std::endl;
		}
	}

	return true;
}
/*--------------------------------------------------------------------
** ���� : LinkFunctionServer
**--------------------------------------------------------------------
** ���� : ���ӹ��ܷ�����
**--------------------------------------------------------------------
** ���� : pszIP IP
** ���� : iPort �˿�
** ���� : iSocket �׽���
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.15		��ΰ
**-------------------------------------------------------------------*/
int Client::LinkFunctionServer(const char* pszIP, int iPort)
{
	if(iPort <= 0)
	{
		return 0;
	}

	//��ʼ��DLL
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if(NO_ERROR != iResult)
	{
		return 0;
	}

	//�����׽���
	SOCKET iListenSocket = INVALID_SOCKET;
	iListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(INVALID_SOCKET == iListenSocket)
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
	service.sin_addr.s_addr = inet_addr(pszIP);
	service.sin_port = htons(iPort);

	//----------------------
	// Bind the socket.
	iResult = connect(iListenSocket, (SOCKADDR *)&service, sizeof(service));
	if(0 != iResult)
	{
		std::cout << "ConnectMainServer Failed " << iResult << std::endl;
	}
	else
	{
		std::cout << "ConnectMainServer Success " << iResult << std::endl;

		const char* pszBuffer = "Hello Users";
		send(iListenSocket, pszBuffer, sizeof(pszBuffer), 0);
	}

	return iListenSocket;
}
/*--------------------------------------------------------------------
** ���� : BroadCast
**--------------------------------------------------------------------
** ���� : �㲥
**--------------------------------------------------------------------
** ���� : iServerFd �������׽���
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.15		��ΰ
**-------------------------------------------------------------------*/
void Client::BroadCast(int iServerFd)
{
	while(1)
	{
		Sleep(5000);
		char recvbuf[DEFAULT_BUFLEN];
		int recvbuflen = DEFAULT_BUFLEN;

		int iResult = recv(iServerFd, recvbuf, recvbuflen, 0);
		if(iResult > 0)
		{
			std::cout << "Reveived BroadCast "<< recvbuf << std::endl;
		}
		else if (0 == iResult)
		{
			std::cout << "Connection Closed!" << std::endl;
		}
		else
		{
			std::cout << "Received Error" << WSAGetLastError() << std::endl;
		}
	}
}

