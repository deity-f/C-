#include"ResManager.h"
#include<iostream>
#include<fstream>
#include<algorithm>
#define PATH_STU "E:/C++/机房预约系统/Student.txt"
#define PATH_TEA "E:/C++/机房预约系统/Teacher.txt"
#define PATH_ADM "E:/C++/机房预约系统/Admin.txt"
#define PATH_ODER "E:/C++/机房预约系统/order.txt"

ResManager::ResManager()
{
	Init();//初始化成员数据
	LoadOrder();//加载请求
	LoadInfo();//加载人物信息
}
void ResManager::Init()
{
	ptr_per = nullptr;
	m_Order.clear();
}
void ResManager::LoadInfo()//load vs_lo....
{
	//load vs_lo
	ifstream ifs(PATH_ODER, ios::in);
	int count = 0;
	string name;
	int core = 0;
	while (ifs >> count && ifs >> name && ifs >> core)
	{
		ptr_per = make_shared<Student>(name, count, core);
		vs_LO.insert(make_pair(count, ptr_per));
	}
	ifs.close();
}
void ResManager::LoadOrder()
{
	ifstream ifs(PATH_ODER, ios::in);
	int account = 0;
	string str = "";
	string str_cut = " ";
	while (getline(ifs, str))
	{
		int pos = str.find(str_cut);
		if (pos == string::npos) {
			continue;  // 如果没有找到分隔符，跳过该行
		}
		string str_acc = str.substr(0, pos);
		int int_acc = 0;

		try {
			int_acc = stoi(str_acc);  // 将账户号从字符串转换为整数
		}
		catch (const std::invalid_argument& e) {
			cout << "无效账户号: " << str_acc << endl;
			continue;  // 如果转换失败，跳过当前行
		}

		string str_info = str.substr(pos + 1, str.size()- pos - 1);
		m_Order.insert(make_pair(int_acc, str_info));
	}
	ifs.close();
	//for (auto it = m_Order.begin(); it != m_Order.end(); it++)
	//{
	//	cout << it->second << endl;
	//}
}
void ResManager::Show_reg()
{
	cout << "*************************************" << endl;
	cout << "***********请选择你的登录身份**********" << endl;
	cout << "**********0.退出管理程序**************" << endl;
	cout << "**********1.学生*********************" << endl;
	cout << "**********2.教师*********************" << endl;
	cout << "**********3.管理员*******************" << endl;
	cout << "************************************" << endl;
}
void ResManager::Exitsystem()
{
	cout << "Welcome to use next time" << endl;
	system("pause");
	exit(0);
}
bool ResManager::Login(int choice)
{
	//测试，直接进入次级界面
	string iname = "老王";
	int iaccount = 1001;
	int icore = 12345;
	//cout << "enter your name:" << endl;
	//cin >> iname;
	//cout << "enter your account:" << endl;
	//cin >> iaccount;
	//cout << "enter your core:" << endl;
	//cin >> icore;
	
	if (1 == choice)//student
	{
		ifstream ifs(PATH_STU, ios::in);
		if (!ifs.is_open())
		{
			cout << "Login is error,please contact the admin " << endl;
			return false;
		}
		string name ;
		int account;
		int core;
		while (ifs >> account && ifs >> name && ifs >> core)
		{
			if (account == iaccount && name == iname && core == icore)
			{
				cout << " login success" << endl;
				ptr_per = make_shared<Student>(name, account, core);//保存登录信息
				ifs.close();
				return true;
			}
		}
		cout << "core error,please enter again" << endl;
		ifs.close();
		return false;
	}
	if (2 == choice)//teacher
	{
		ifstream ifs(PATH_TEA, ios::in);
		if (!ifs.is_open())
		{
			cout << "Login is error,please contact the admin " << endl;
			return false;
		}
		string name;
		int account;
		int core;
		while (ifs >> account && ifs >> name && ifs >> core)
		{
			if (account == iaccount && name == iname && core == icore)
			{
				cout << " login success" << endl;
				ptr_per = make_shared<Teacher>(name, account, core);
				ifs.close();
				return true;
			}
		}
		cout << "core error,please enter again" << endl;
		ifs.close();
		return false;
	}
	ifstream ifs(PATH_ADM, ios::in);//admin
	if (!ifs.is_open())
	{
		cout << "Login is error,please contact the admin " << endl;
		return false;
	}
	string name;
	int account;
	int core;
	while (ifs >> account && ifs >> name && ifs >> core)
	{
		if (account == iaccount && name == iname && core == icore)
		{
			cout << " login success" << endl;
			ptr_per = make_shared<Admin>(name, core);
			ifs.close();
			return true;
		}
	}
	cout << "core error,please enter again" << endl;
	ifs.close();
	return false;

}
//void ResManager::Show_Sceond(int choice)
//{
//	if (choice == 1)
//	{
//		cout << "*************************************" << endl;
//		cout << "**********1.申请预约******************" << endl;
//		cout << "**********2.查看自身预约**************" << endl;
//		cout << "**********3.查看所有预约**************" << endl;
//		cout << "**********4.取消预约******************" << endl;
//		cout << "**********0.注销登录******************" << endl;
//		cout << "************************************" << endl;
//	}
//	if (choice == 2)
//	{
//		cout << "*************************************" << endl;
//		cout << "**********1.查看所有预约***************" << endl;
//		cout << "**********2.审核预约******************" << endl;
//		cout << "**********0.注销登录******************" << endl;
//		cout << "************************************" << endl;
//	}
//	if (choice == 3)
//	{
//		cout << "*************************************" << endl;
//		cout << "**********1.添加账号******************" << endl;
//		cout << "**********2.查看账号******************" << endl;
//		cout << "**********3.查看机房******************" << endl;
//		cout << "************************************" << endl;
//	}
//}
void ResManager::Oper(int choice)
{
	int flag = Login(choice);//登录，并让智能指针ptr_per指向所选择的身份
	if (flag == false)//code error
	{
		return;
	}
	system("pause");
	system("cls");
	while (1)
	{
		//ptr_per->Show_oper();//show menu
		if (choice == 1)
		{
			//unique_ptr<Student> ptr_stu = dynamic_unique_cast<Student>(move(ptr_per));//指向学生类
			ptr_per->Show_oper();//show menu
			shared_ptr<Student> ptr_stu = dynamic_pointer_cast<Student>(ptr_per);//向下转换为子类指针
			int choice_stu;
			cout << "choice your operate:" << endl;
			cout << "1.reserve the motor room 2.check yourself reserve 3.check all reserve 4.cancel your reserve 0.exit login" << endl;
			cin >> choice_stu;
			switch (choice_stu)
			{
			case 1://预约机房
				ptr_stu->reserve_Stu(m_Order);
				break;
			case 2://查看自身预约
				//ptr_stu->Get_Time(m_Order);
				ptr_stu->CheckRes_self(m_Order);
				break;
			case 3://查看所有预约
				ptr_stu->CheckRes_all(m_Order);
				break;
			case 4://取消预约
				ptr_stu->CancelRes(m_Order);
				break;
			case 0://退出登录
				cout << "login successfully logged out" << endl;
				return;
				break;
			}

		}
		if (choice == 2)
		{
			ptr_per->Show_oper();//show menu
			shared_ptr<Teacher> ptr_tea = dynamic_pointer_cast<Teacher>(ptr_per);//向下转换为子类指针
			int choice_tea;
			cout << "choice your operate:" << endl;
			cout << "1. check all reserve 2. verify the reserve 0. exit login" << endl;
			cin >> choice_tea;
			switch (choice_tea)
			{
			case 1://查看所有预约
				ptr_tea->CheckRes_all(m_Order);
				break;
			case 2://审核预约
				//ptr_stu->Get_Time(m_Order);
				ptr_tea->VerifyRes(m_Order, m1_t,m2_t, m3_t,vs_LO);
				break;

			case 0://退出登录
				cout << "login successfully logged out" << endl;
				return;
				break;
			}
		}
		if (choice == 3)
		{

		}
		system("pause");
		system("cls");
	}
}
//void ResManager::Act_Stu()
//{
//	int flag = Login(1);
//	system("pause");
//	system("cls");
//	if (flag == false)//code error
//	{
//		return;
//	}
//	while (1)
//	{
//		int choice = 0;
//		Show_Sceond(1);//show menu
//		cout << "choice your operate:" << endl;
//		cout << "1.reserve the motor room 2.check yourself reserve 3.check all reserve 4.cancel your reserve 5.exit login" << endl;
//		cin >> choice;
//		switch (choice)
//		{
//		case 1://预约机房
//			this->reserve_Stu();
//			break;
//		case 2://查看自身预约
//			break;
//		case 3://查看所有预约
//			break;
//		case 4://取消预约
//			break;
//		case 5://退出登录
//			break;
//		}
//	}
//}
