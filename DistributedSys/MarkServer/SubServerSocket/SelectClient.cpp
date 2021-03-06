#include "SelectClient.h"

SelectClient * SelectClient::m_pSelectClient = NULL;
/*--------------------------------------------------------------------
** 名称 : SelectClient
**--------------------------------------------------------------------
** 功能 : 初始化
**--------------------------------------------------------------------
** 参数 : NULL
** 返值 : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.10		Mark
**-------------------------------------------------------------------*/
SelectClient::SelectClient()
{
	m_pSelectClient = this;
}

/*--------------------------------------------------------------------
** 名称 : ~SubServer
**--------------------------------------------------------------------
** 功能 : 释放
**--------------------------------------------------------------------
** 参数 : NULL
** 返值 : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.10		Mark
**-------------------------------------------------------------------*/
SelectClient::~SelectClient()
{
	delete m_thSelectClient;

}

/*--------------------------------------------------------------------
** 名称 : InitNetService
**--------------------------------------------------------------------
** 功能 : 初始化网络服务
**--------------------------------------------------------------------
** 参数 : NULL
** 返值 : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.10		Mark
**-------------------------------------------------------------------*/
bool SelectClient::InitNetService()
{
	int iServerfd = InitSocket();

	// 处理客户端连接
	m_thSelectClient = new std::thread(th_DealClientConnect,iServerfd); 	
	return true;
}

/*--------------------------------------------------------------------
** 名称 : InitSocket
**--------------------------------------------------------------------
** 功能 : 初始化网络
**--------------------------------------------------------------------
** 参数 : NULL
** 返值 : serverfd
**--------------------------------------------------------------------
** Date:		Name
** 19.02.10		Mark
**-------------------------------------------------------------------*/
int SelectClient::InitSocket()
{
	//初始化DLL
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if(NO_ERROR != iResult)
	{
		return 0;
	}

	//创建套接字
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
** 名称 : th_DealClientConnect
**--------------------------------------------------------------------
** 功能 : 处理网络请求
**--------------------------------------------------------------------
** 参数 : NULL
** 返值 : serverfd
**--------------------------------------------------------------------
** Date:		Name
** 19.02.10		Mark
**-------------------------------------------------------------------*/
bool SelectClient::th_DealClientConnect(int iServerfd)
{
	if(0 == iServerfd)
	{
		return false;
	}

	fd_set client_fdset;	/*监控文件描述符集合*/
	struct timeval tv;		/*超时返回时间*/

	tv.tv_sec = 10;
	tv.tv_usec = 0;

	int conn_amount = 0;    //用来记录描述符数量
	SOCKET client_sockfd[5] = {0};   //存放活动的sockfd
	int iMaxsock;            //监控文件描述符中最大的文件号
	iMaxsock = iServerfd;

	char buffer[256];
	memset(buffer, '\0', sizeof(buffer));

	while(1)
	{
		/*初始化文件描述符号到集合*/
		FD_ZERO(&client_fdset);

		/*加入服务器描述符*/
		FD_SET(iServerfd, &client_fdset);

		//把活动的句柄加入到文件描述符中
		for (int i = 0; i < 5; ++i)
		{
			//程序中Listen中参数设为5,故i必须小于5
			if (client_sockfd[i] != 0)
			{
				FD_SET(client_sockfd[i], &client_fdset);
			}
		}
		int ret = select(iMaxsock + 1, &client_fdset, NULL, NULL, &tv);
		if(ret < 0) // 出错 -1
		{
			perror("select error!\n");
			
			int i = WSAGetLastError();
			
			break;
			
		}
		else if(ret == 0) // 超时 0
		{
			//printf("timeout!\n");
	
			continue;
		}


		// 检测是否有网络IO请求
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
					OnCustomChat(buffer);
					memset(buffer, '\0', sizeof(buffer));

				}
				
			}
		}

		// 检测是否有新的连接
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

			// 把连接加入到新的文件描述符集合中
			if(conn_amount < 5)
			{
				int iConnRank = conn_amount;
				int iClientFd = iSock_client;

				client_sockfd[conn_amount++] = iSock_client;
				
				std::cout << "sock_client " << iSock_client << "Accept" << std::endl;

				m_pSelectClient->m_MapClientFd.insert(std::make_pair(iConnRank, iClientFd));
			}
		
		}


	}
	return true;
}

/*--------------------------------------------------------------------
** 名称 : OnCustomChat
**--------------------------------------------------------------------
** 功能 : 处理客户端聊天消息
**--------------------------------------------------------------------
** 参数 : sock_client 客户端连接
** 返值 : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.10		Mark
**-------------------------------------------------------------------*/
void SelectClient::OnCustomChat(char*  bufferSend) // 设计成类似群聊
{
	if(0 == strlen(bufferSend))
	{
		return;
	}

	int iSubMsg;
	char szTxt[256];
	memset(szTxt, '\0', sizeof(szTxt));
	int iMsg = ReadClientMsg(bufferSend, iSubMsg,szTxt);
	if(0 == iMsg)
	{
		return;
	}
	switch(iMsg)
	{
		case CLIENT_SUSTOM_MSG_PLAYER_LIST: // 玩家列表
			{
				OnSubCustomPlayerList(bufferSend);
			}
			break;
		case CLIENT_SUSTOM_MSG_SINGLE_CHAT : // 单聊
			{

			}
			break;
		case CLIENT_SUSTOM_MSG_MAKE_GROUP: // 建立讨论组
			{
			}
			break;
		case CLIENT_SUSTOM_MSG_GROUP_CHAT:// 群聊
			{
				OnSubCustomGroupChat(iSubMsg, szTxt);
			}
			break;
		default:
			break;

	}
	
}
/*--------------------------------------------------------------------
** 名称 : OnSubCustomPlayerList
**--------------------------------------------------------------------
** 功能 : 群聊
**--------------------------------------------------------------------
** 参数 : bufferSend 客户端内容
** 返值 : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.10		Mark
**-------------------------------------------------------------------*/
void SelectClient::OnSubCustomPlayerList(char*  bufferSend)
{
	char pszRecvChat[256];
	memset(pszRecvChat, '\0', sizeof(pszRecvChat));

	MapClientFd::iterator itClientFd = m_pSelectClient->m_MapClientFd.begin();
	for (itClientFd; itClientFd != m_pSelectClient->m_MapClientFd.end(); itClientFd++)
	{
		int iClientRank = itClientFd->first;
		int iClientFd = itClientFd->second;

		send(iClientFd, pszRecvChat, strlen(pszRecvChat), 0);
	}

	memset(pszRecvChat, '\0', sizeof(pszRecvChat));
}

/*--------------------------------------------------------------------
** 名称 : OnSubCustomGroupChat
**--------------------------------------------------------------------
** 功能 : 群聊
**--------------------------------------------------------------------
** 参数 : iSubMsg 客户端子消息
** 参数 : pszRecvChat 聊天内容
** 返值 : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.10		Mark
**-------------------------------------------------------------------*/
void SelectClient::OnSubCustomGroupChat(int iSubMsg, char* pszRecvChat)
{
	if(0 == strlen(pszRecvChat))
	{
		return;
	}

	MapClientFd::iterator itClientFd = m_pSelectClient-> m_MapClientFd.begin();
	for(itClientFd;itClientFd!= m_pSelectClient->m_MapClientFd.end();itClientFd++)
	{
	//	int iClientRank = itClientFd->first;
		int iClientFd = itClientFd->second;

		send(iClientFd, pszRecvChat, strlen(pszRecvChat), 0);
	}

	memset(pszRecvChat, '\0', sizeof(pszRecvChat));
}

/*--------------------------------------------------------------------
** 名称 : QuerySockClient
**--------------------------------------------------------------------
** 功能 : 查询新增客户端套接字
**--------------------------------------------------------------------
** 参数 : NULL
** 返值 : 新增客户端套接字
**--------------------------------------------------------------------
** Date:		Name
** 19.02.18		Mark
**-------------------------------------------------------------------*/
int SelectClient::QuerySockClient()
{
	int iSocket_client = m_pSelectClient->m_iSock_client;

	return iSocket_client;
}
/*--------------------------------------------------------------------
** 名称 : SetSocketClient
**--------------------------------------------------------------------
** 功能 : 设置新增客户端套接字
**--------------------------------------------------------------------
** 参数 : iSock_client 新增客户端套接字
** 返值 : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.18	    Mark
**-------------------------------------------------------------------*/
void SelectClient::SetSocketClient(int iSock_client)
{
	if(iSock_client >0)
	{
		m_pSelectClient->m_iSock_client = iSock_client;
	}
	
}
/*--------------------------------------------------------------------
** 名称 : ReadClientMsg
**--------------------------------------------------------------------
** 功能 : 读取客户端消息
**--------------------------------------------------------------------
** 参数 : bufferSend 客户端消息
** 参数 : iSubMsg 客户端子消息
** 参数 : szTxt 文本内容
** 返值 : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.25	    Mark
**-------------------------------------------------------------------*/
int SelectClient::ReadClientMsg(char* bufferSend, int &iSubMsg, char* szTxt)
{
	int iMsg = atoi(bufferSend);

	return iMsg;
}
