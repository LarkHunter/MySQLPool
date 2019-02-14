#include "SelectClientSocket.h"
#include "AcceptServerSocket.h"

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
** ���� : StartNetService
**--------------------------------------------------------------------
** ���� : ��ʼ���������
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : �׽���
**--------------------------------------------------------------------
** Date:		Name
** 19.02.14		��ΰ
**-------------------------------------------------------------------*/
bool SelectClientSocket::StartNetService()
{
	// ��ʼ������
	int iSeverFd = InitSocket();

	if(iSeverFd <=0)
	{
		return false;
	}

	// ��ѯ�׿ͻ�������
	bool bResult = SelectCilentConnect(iSeverFd);

	return bResult;

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
	service.sin_port = htons(6666);

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
/*--------------------------------------------------------------------
** ���� : SelectCilentConnect
**--------------------------------------------------------------------
** ���� : ��ѯ�ͻ�������
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : serverfd
**--------------------------------------------------------------------
** Date:		Name
** 19.02.14		��ΰ
**-------------------------------------------------------------------*/
bool SelectClientSocket::SelectCilentConnect(int iSeverSocketfd)
{
	if (0 == iSeverSocketfd)
	{
		return false;
	}

	fd_set client_fdset;	/*����ļ�����������*/
	struct timeval tv;		/*��ʱ����ʱ��*/

	tv.tv_sec = 5;
	tv.tv_usec = 0;
	while (1)
	{
		/*��ʼ���ļ��������ŵ�����*/
		FD_ZERO(&client_fdset);

		/*���������������*/
		FD_SET(iSeverSocketfd, &client_fdset);

		int ret = select(iSeverSocketfd + 1, &client_fdset, NULL, NULL, &tv);
		if(ret < 0) // ���� -1
		{
			perror("select error!\n");

			Sleep(5000);
			continue;

			//break;
		}
		else if (ret == 0) // ��ʱ 0
		{
			printf("timeout!\n");

			continue;
		}

		if(FD_ISSET(iSeverSocketfd, &client_fdset))
		{
			struct sockaddr_in client_addr;
			size_t size = sizeof(struct sockaddr_in);

			int sock_client = accept(iSeverSocketfd, NULL, NULL);
			if(sock_client < 0)
			{
				perror("accept error!\n");
				continue;
			}
			else
			{
				std::cout << "sock_client " << sock_client << "Accept" << std::endl;

				m_vecClientFd.push_back(sock_client);

				// Ϊ�ͻ��˷����ӷ����� 
				int iSubServerSocket = AllocateSubServer(); 
				send(sock_client, (char*)&iSubServerSocket, sizeof(iSubServerSocket), 0);

			}

		}

	}
	return true;
}
/*--------------------------------------------------------------------
** ���� : AllocateSubServer
**--------------------------------------------------------------------
** ���� : �����ӷ�����
**--------------------------------------------------------------------
** ���� : NULL
** ��ֵ : NULL
**--------------------------------------------------------------------
** Date:		Name
** 19.02.14		��ΰ
**-------------------------------------------------------------------*/
int SelectClientSocket::AllocateSubServer()
{
	VecSubServerSocket vecSubServerSocket;

	AcceptServerSocket::QueryOnlineSubServer(vecSubServerSocket);

	int iSize = static_cast<int>(vecSubServerSocket.size());

	int iCount = rand() % iSize;

	if(iCount <= 0
		|| iCount >= iSize)
	{
		return 0;
	}

	int iSocket = vecSubServerSocket.at(iCount);

	return iSocket;
}
