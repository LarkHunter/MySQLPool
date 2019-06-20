#include <iostream>
#include "IRecord.h"

int main()
{
	IRecord m_Record;

	m_Record.ChooseDatabase();

	Statement * state = m_Record.GetRecord("baotou");

	ResultSet *result;

	result = state->executeQuery("select * from baotou");
	
	// Êä³ö²éÑ¯
	while(result->next())
	{
		int iID = result->getInt("id");
// 		std::string strName = result->getString("name");
// 		std::string strPwd = result->getString("pwd");
// 
// 		cout << iID << ":" << strName << ":" << strPwd << endl;
		const char* pszName = (result->getString("name")).c_str();
		const char* pszPwd = (result->getString("pwd")).c_str();

 		cout << "ID = "<< iID<< endl;
 		cout << "pszName = "<< pszName << endl;
 		cout <<"pszPwd = " << pszPwd << endl;
	}
	system("pause");
	return 0;
}