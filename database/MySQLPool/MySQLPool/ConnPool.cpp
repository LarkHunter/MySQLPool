#include "ConnPool.h"

ConnPool*ConnPool::m_pConnPoolModule = NULL;

ConnPool*ConnPool::m_connPoolIntance = new ConnPool("tcp://127.0.0.1:3306", "root", "123456", 50);

// �������ݿ����ӳض���
ConnPool::ConnPool(const char* pszUrl /*= ""*/, const char* pszUser /*=""*/, const char* pszPwd /*= ""*/, int iMaxSize /*= 0*/)
{
	m_pConnPoolModule = this;

	InitConnPoolByCfg(); // ͨ�������ļ���ʼ�����ݿ�

	if(NULL != pszUrl)
	{
		m_strDBUrl = pszUrl;
	}

	if(NULL != pszUser)
	{
		m_strDBUser = pszUser;
	}

	if(NULL != pszPwd)
	{
		m_strDBPwd = pszPwd;
	}

	if(iMaxSize > 0)
	{
		m_iDBPoolMaxSize;
	}

	try
	{
		m_pConnPoolModule->m_driver = sql::mysql::get_driver_instance();
	}
	catch (...)
	{
		std::cout << "ConnPool Got Driver Failed!"<< std::endl;
	}
	
}

// �������ļ���ʼ�����ӳض���
void ConnPool::InitConnPoolByCfg()
{

}

// ��ʼ������
void ConnPool::InitConnection(int iConnectNum)
{
	Connection *conn;
	m_pConnPoolModule->m_mutex.lock();

	for(int i = 0;i < iConnectNum; i++)
	{
		try
		{
			conn = CreateConnection(); // ����һ������
		}
		catch (...)
		{
			std::cout << " Create Connection Failed!" << std::endl;
			continue;
		}
		
		m_pConnPoolModule->m_lConnList.push_back(conn);
	}

	m_pConnPoolModule->m_mutex.unlock();
}


// ����һ������
Connection* ConnPool::CreateConnection()
{
	Connection* conn;
	try
	{
		conn = m_pConnPoolModule->m_driver->connect(m_pConnPoolModule->m_strDBUrl, m_pConnPoolModule->m_strDBUser, m_pConnPoolModule->m_strDBPwd); // ��������

	}
	catch(...)
	{
		std::cout << "Connect Error"<< std::endl;
	}
	
	return conn;
}

// ����һ�����ݿ�����
void ConnPool::CloseAConnection(Connection* conn)
{
	if(!conn)
	{
		return;
	}

	try
	{
		conn->close();
	}
	catch (...)
	{
		cout << "CLose Connection Failed"<<endl;

		return;
	}
	
}

// �������ݿ����ӳ�
void ConnPool::DestoryConnPool()
{
	m_mutex.lock();

	LConnList::iterator itConn; // ���ӳص�����
	for(itConn = m_lConnList.begin();itConn!=m_lConnList.end();itConn++)
	{
		CloseAConnection(*itConn);
	}

	m_lConnList.clear();

	m_mutex.unlock();
}

ConnPool::~ConnPool()
{
	this->DestoryConnPool();
}

// ��ȡ���ݿ�ʵ������
ConnPool * ConnPool::GetConnInstance()
{
	if(NULL == m_connPoolIntance)
	{
		return NULL;
	}

	return m_connPoolIntance;
}

// ��ȡ���ݿ�����
Connection * ConnPool::GetConnection()
{
	Connection* conn;

	m_mutex.lock();

	int iSize = static_cast<int>(m_lConnList.size()); // ȡ�����ӳ�����

	if(iSize >0) // ���ӳ��������ӵ����
	{
		conn = m_lConnList.front(); // �õ���һ������
		m_lConnList.pop_front(); // ���ӳ����Ƴ���һ������

		if(conn->isClosed())
		{
			delete conn;

			try
			{
				conn = this->CreateConnection();

				return conn;
			}
			catch (...)
			{
				std::cout << " Create Connection Failed" << std::endl;

				return NULL;
			}

		}
		else
		{
			return conn;
		}

		m_mutex.unlock();
	}
	else
	{
		if(iSize >= m_iDBPoolMaxSize)
		{
			m_mutex.unlock();

			return NULL;
		}
		else
		{
			try
			{
				conn = this->CreateConnection();

				return conn;
			}
			catch(...)
			{
				std::cout << " Create Connection Failed" << std::endl;
				
				m_mutex.unlock();

				return NULL;
			}
		}

	}

	//m_mutex.unlock();

	//return conn;
}

// �黹����
void ConnPool::BackConnection(sql::Connection * conn)
{
	if(conn)
	{
		m_mutex.lock();
		m_lConnList.push_back(conn);
		m_mutex.unlock();
	}
}
