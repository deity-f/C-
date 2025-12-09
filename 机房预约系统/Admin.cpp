#include"Admin.h"

Admin::Admin(string name, int core)
{
	m_name = name;
	m_Core = core;
}
void Admin::Show_oper()
{
	cout << "*************************************" << endl;
	cout << "**********1.添加账号******************" << endl;
	cout << "**********2.查看账号******************" << endl;
	cout << "**********3.查看机房******************" << endl;
	cout << "************************************" << endl;
}