#include "SelectClient.h"

SelectClient * SelectClient::m_pSelectClient = NULL;
/*--------------------------------------------------------------------
** ���� : SelectClient
**--------------------------------------------------------------------
** ���� : ��ʼ��
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.10		��ΰ
**-------------------------------------------------------------------*/
SelectClient::SelectClient()
{
	m_pSelectClient = this;
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
SelectClient::~SelectClient()
{
	delete m_thSelectClient;

	delete m_thBroadCast;
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
bool SelectClient::InitNetService()
{
	int iServerfd = InitSocket();

	// ����ͻ�������
	m_thSelectClient = new std::thread(th_DealClientConnect,iServerfd); 

	// ��������㲥
	m_thBroadCast = new std::thread(th_BroadCast);
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
int SelectClient::InitSocket()
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
	service.sin_port = htons(9999);

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
** ���� : th_DealClientConnect
**--------------------------------------------------------------------
** ���� : ������������
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : serverfd
**--------------------------------------------------------------------
** Date:		Name
** 19.02.10		��ΰ
**-------------------------------------------------------------------*/
bool SelectClient::th_DealClientConnect(int iServerfd)
{
	if(0 == iServerfd)
	{
		return false;
	}

	fd_set client_fdset;	/*����ļ�����������*/
	struct timeval tv;		/*��ʱ����ʱ��*/

	tv.tv_sec = 10;
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
			//printf("timeout!\n");
	
			continue;
		}

		if(FD_ISSET(iServerfd, &client_fdset))
		{
			struct sockaddr_in client_addr;
			size_t size = sizeof(struct sockaddr_in);

			int iSock_client = accept(iServerfd, NULL, NULL);
			if(iSock_client < 0)
			{
				perror("accept error!\n");
				continue;
			}
			else
			{
				std::cout << "sock_client "<< iSock_client <<"Accept"<< std::endl;
				
				m_pSelectClient->m_VecClientFd.push_back(iSock_client);

				SetSocketClient(iSock_client);
				
				//int iSend = 666;
			//	send(sock_client, (char*)&iSend, sizeof(iSend), 0);

			}

		}

	}
	return true;
}
/*--------------------------------------------------------------------
** ���� : th_BroadCast
**--------------------------------------------------------------------
** ���� : ����㲥
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.18		��ΰ
**-------------------------------------------------------------------*/
bool SelectClient::th_BroadCast()
{
	
	while(true)
	{
		int iSock_Client = QuerySockClient();
		//DealBroadCast(iSock_Client);

		char buffer[256];//�����1024 ��ô���������4��
		memset(buffer, 0, sizeof(buffer));
		int ret = recv(iSock_Client, buffer, 1024, MSG_PEEK); // �漰������
		if(ret < 0)
		{

		}
		else
		{
			std::cout << "buffer"<< buffer << std::endl;
		}

		Sleep(5000);
	}
}

/*--------------------------------------------------------------------
** ���� : DealBroadCast
**--------------------------------------------------------------------
** ���� : ����㲥
**--------------------------------------------------------------------
** ���� : sock_client �ͻ�������
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.10		��ΰ
**-------------------------------------------------------------------*/
void SelectClient::DealBroadCast(int sock_client) // ��Ƴ�����Ⱥ��
{
	char buffer[256];//�����1024 ��ô���������4��
	memset(buffer, 0, sizeof(buffer));
	
	//int ret = recv(sock_client, buffer, 1024, 0); // �漰������
	sockaddr_in SenderAddr;
	int SenderAddrSize = sizeof(SenderAddr);

	//int ret = recvfrom(sock_client, buffer, 256, MSG_PEEK, (SOCKADDR *)& SenderAddr, &SenderAddrSize);
	int ret = recv(sock_client, buffer, 1024, MSG_PEEK); // �漰������
	if(ret < 0)
	{
		//perror("recv error!\n");
				
		//WSACleanup();
		return;
	}
	else if(ret > 0)
	{
		std::cout << "buffer = " << buffer << std::endl;
		VecClientFd::iterator itClientFd = m_pSelectClient->m_VecClientFd.begin();
		for (itClientFd; itClientFd != m_pSelectClient->m_VecClientFd.end(); itClientFd++)
		{
			int iClientFd = *itClientFd;
			send(iClientFd, buffer, sizeof(buffer), 0);
		}
	}

}
/*--------------------------------------------------------------------
** ���� : QuerySockClient
**--------------------------------------------------------------------
** ���� : ��ѯ�����ͻ����׽���
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : �����ͻ����׽���
**--------------------------------------------------------------------
** Date:		Name
** 19.02.18	��ΰ
**-------------------------------------------------------------------*/
int SelectClient::QuerySockClient()
{
	int iSocket_client = m_pSelectClient->m_iSock_client;

	return iSocket_client;
}
/*--------------------------------------------------------------------
** ���� : SetSocketClient
**--------------------------------------------------------------------
** ���� : ���������ͻ����׽���
**--------------------------------------------------------------------
** ���� : iSock_client �����ͻ����׽���
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.18	��ΰ
**-------------------------------------------------------------------*/
void SelectClient::SetSocketClient(int iSock_client)
{
	if(iSock_client >0)
	{
		m_pSelectClient->m_iSock_client = iSock_client;
	}
	
}
