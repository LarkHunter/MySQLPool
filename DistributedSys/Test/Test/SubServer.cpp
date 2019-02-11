#include "SubServer.h"


/*--------------------------------------------------------------------
** ���� : SubServer
**--------------------------------------------------------------------
** ���� : ��ʼ��
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.10		��ΰ
**-------------------------------------------------------------------*/
SubServer::SubServer()
{
}

/*--------------------------------------------------------------------
** ���� : ~SubServer
**--------------------------------------------------------------------
** ���� : �ͷ�
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.10		��ΰ
**-------------------------------------------------------------------*/
SubServer::~SubServer()
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
bool SubServer::InitNetService()
{
	int iServerfd = InitSocket();

	DealNetRequest(iServerfd); // ������������

	return true;
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
** 19.02.10		��ΰ
**-------------------------------------------------------------------*/
int SubServer::InitSocket()
{
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
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(27015);

	//----------------------
	// Bind the socket.
	iResult = bind(iListenSocket, (SOCKADDR *)&service, sizeof(service));
	if(INVALID_SOCKET == iResult)
	{
		WSACleanup();

		return 0;
	}
	else
	{
		std::cout << "Bind Socket Success" << std::endl;
	}

	int iRet = listen(iListenSocket, SOMAXCONN);
	if(0 != iRet)
	{
		return 0;
	}
	else
	{
		std::cout << "Listen Socket Success" << std::endl;
	}

	return iListenSocket;
}
/*--------------------------------------------------------------------
** ���� : DealNetRequest
**--------------------------------------------------------------------
** ���� : ������������
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : serverfd
**--------------------------------------------------------------------
** Date:		Name
** 19.02.10		��ΰ
**-------------------------------------------------------------------*/
bool SubServer::DealNetRequest(int iServerfd)
{
	if(0 == iServerfd)
	{
		return false;
	}

	fd_set client_fdset;	/*����ļ�����������*/
	struct timeval tv;		/*��ʱ����ʱ��*/

	tv.tv_sec = 5;
	tv.tv_usec = 0;
	while(1)
	{
		/*��ʼ���ļ��������ŵ�����*/
		FD_ZERO(&client_fdset);

		/*���������������*/
		FD_SET(iServerfd, &client_fdset);

		int ret = select(iServerfd + 1, &client_fdset, NULL, NULL, &tv);
		if(ret < 0) // ���� -1
		{
			perror("select error!\n");
			
			Sleep(5000);
			continue;
			
			//break;
		}
		else if(ret == 0) // ��ʱ 0
		{
			printf("timeout!\n");
	
			continue;
		}

		if(FD_ISSET(iServerfd, &client_fdset))
		{
			struct sockaddr_in client_addr;
			size_t size = sizeof(struct sockaddr_in);

			int sock_client = accept(iServerfd, NULL, NULL);
			if(sock_client < 0)
			{
				perror("accept error!\n");
				continue;
			}
			else
			{
				std::cout << "sock_client "<< sock_client <<"Accept"<< std::endl;
				
				m_VecClientFd.push_back(sock_client);
			}

			char buffer[1024];
			memset(buffer, 0, sizeof(buffer));

			ret = recv(sock_client, buffer, 1024, 0);
			if(ret < 0)
			{
				perror("recv error!\n");
				
				WSACleanup();

				//return f;
			}

			printf("recv : %s\n", buffer);
		}

	}
	return true;
}
