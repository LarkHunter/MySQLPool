#include "ConnPool.h"

ConnPool*ConnPool::m_pConnPoolModule = NULL;

ConnPool*ConnPool::m_connPoolIntance = new ConnPool("tcp://127.0.0.1:3306", "root", "123456", 50);

// 构造数据库连接池对象
ConnPool::ConnPool(const char* pszUrl /*= ""*/, const char* pszUser /*=""*/, const char* pszPwd /*= ""*/, int iMaxSize /*= 0*/)
{
	m_pConnPoolModule = this;

	InitConnPoolByCfg(); // 通过配置文件初始化数据库

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

// 由配置文件初始化连接池对象
void ConnPool::InitConnPoolByCfg()
{

}

// 初始化连接
void ConnPool::InitConnection(int iConnectNum)
{
	Connection *conn;
	m_pConnPoolModule->m_mutex.lock();

	for(int i = 0;i < iConnectNum; i++)
	{
		try
		{
			conn = CreateConnection(); // 创建一个连接
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


// 创建一个连接
Connection* ConnPool::CreateConnection()
{
	Connection* conn;
	try
	{
		conn = m_pConnPoolModule->m_driver->connect(m_pConnPoolModule->m_strDBUrl, m_pConnPoolModule->m_strDBUser, m_pConnPoolModule->m_strDBPwd); // 建立连接

	}
	catch(...)
	{
		std::cout << "Connect Error"<< std::endl;
	}
	
	return conn;
}

// 销毁一个数据库连接
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

// 销毁数据库连接池
void ConnPool::DestoryConnPool()
{
	m_mutex.lock();

	LConnList::iterator itConn; // 连接池迭代器
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

// 获取数据库实例对象
ConnPool * ConnPool::GetConnInstance()
{
	if(NULL == m_connPoolIntance)
	{
		return NULL;
	}

	return m_connPoolIntance;
}

// 获取数据库连接
Connection * ConnPool::GetConnection()
{
	Connection* conn;

	m_mutex.lock();

	int iSize = static_cast<int>(m_lConnList.size()); // 取出连接池数量

	if(iSize >0) // 连接池中有连接的情况
	{
		conn = m_lConnList.front(); // 得到第一个连接
		m_lConnList.pop_front(); // 连接池中移除第一个连接

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

// 归还连接
void ConnPool::BackConnection(sql::Connection * conn)
{
	if(conn)
	{
		m_mutex.lock();
		m_lConnList.push_back(conn);
		m_mutex.unlock();
	}
}
