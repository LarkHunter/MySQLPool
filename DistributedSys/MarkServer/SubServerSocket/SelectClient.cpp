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
	//service.sin_zero = 0;
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

	int conn_amount = 0;    //������¼����������
	SOCKET client_sockfd[5] = {0};   //��Ż��sockfd
	int iMaxsock;            //����ļ��������������ļ���
	iMaxsock = iServerfd;

	char buffer[256];
	memset(buffer, '\0', sizeof(buffer));

	while(1)
	{
		/*��ʼ���ļ��������ŵ�����*/
		FD_ZERO(&client_fdset);

		/*���������������*/
		FD_SET(iServerfd, &client_fdset);

		//�ѻ�ľ�����뵽�ļ���������
		for (int i = 0; i < 5; ++i)
		{
			//������Listen�в�����Ϊ5,��i����С��5
			if (client_sockfd[i] != 0)
			{
				FD_SET(client_sockfd[i], &client_fdset);
			}
		}
		int ret = select(iMaxsock + 1, &client_fdset, NULL, NULL, &tv);
		if(ret < 0) // ���� -1
		{
			perror("select error!\n");
			
			int i = WSAGetLastError();
			
			break;
			
		}
		else if(ret == 0) // ��ʱ 0
		{
			//printf("timeout!\n");
	
			continue;
		}


		// ����Ƿ�������IO����
		for (int i = 0; i < conn_amount; i++)
		{
			if (FD_ISSET(client_sockfd[i], &client_fdset))
			{
				int iClientFd = client_sockfd[i];
				ret = recv(iClientFd, buffer, 1024, 0);
				if (ret < 0)
				{
					//return -1;
					FD_CLR(client_sockfd[i], &client_fdset);
					client_sockfd[i] = 0;
				}
				else
				{
					std::cout << "buffer = " << buffer << "strlen(buffer)"<< strlen(buffer) <<std::endl;
					DealBroadCast(buffer);
					memset(buffer, '\0', sizeof(buffer));

				}
				
			}
		}

		// ����Ƿ����µ�����
		if(FD_ISSET(iServerfd, &client_fdset))
		{
			struct sockaddr_in client_addr;
			size_t size = sizeof(struct sockaddr_in);

			int iSock_client = accept(iServerfd, (struct sockaddr*)(&client_addr), (int*)(&size));
			if(iSock_client < 0)
			{
				perror("accept error!\n");
				continue;
			}

			// �����Ӽ��뵽�µ��ļ�������������
			if(conn_amount < 5)
			{
				client_sockfd[conn_amount++] = iSock_client;
				
				std::cout << "sock_client " << iSock_client << "Accept" << std::endl;
				m_pSelectClient->m_VecClientFd.push_back(iSock_client);
			}
		
		}


	}
	return true;
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
void SelectClient::DealBroadCast(char*  bufferSend) // ��Ƴ�����Ⱥ��
{
	if(0 == strlen(bufferSend))
	{
		return;
	}

	VecClientFd::iterator itClientFd = m_pSelectClient->m_VecClientFd.begin();
	for (itClientFd; itClientFd != m_pSelectClient->m_VecClientFd.end(); itClientFd++)
	{
		int iClientFd = *itClientFd;
		send(iClientFd, bufferSend, strlen(bufferSend), 0);

		std::cout << "BroadCast size =  "<< strlen(bufferSend) <<"Info = " << bufferSend<<std::endl;

	}
	memset(bufferSend, '\0', sizeof(bufferSend));
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
