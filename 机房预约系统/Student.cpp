#include"Student.h"
#define PATH_ODER "E:/C++/机房预约系统/order.txt"
#define FLAG_RES_CANCEL 3
#define FLAG_RES_PASS 1
#define FLAG_RES_ING 0
Student::Student()
{
	Init();
}
Student::Student(string name, int account, int core)
{
	Init();
	m_name = name;
	m_Account = account;
	m_Core = core;
}
void Student::Init()
{
	flag_Res = "预约审核中";
}
string Student::Get_Info(map<int, string>& m_Order,int index)
{
	int count = 0;
	int pos = 0;
	string str_time;
	string Room;
	string Time;
	string SepTime;
	string str_name;
	string str_info = m_Order[index];
	for (auto it = str_info.begin(); it != str_info.end(); it++,pos++)//获取到order文件中关于时间的信息，后三个数
	{
		if (*it == ' ')
		{
			count++;
		}
		if (count >= 1 && *it != ' ')
		{
			str_name = str_info.substr(0, pos - 1);
			str_time = str_info.substr(pos, str_info.size() - pos);
			break;
		}
	}
	if (str_time[0] == '1')
	{
		Room = "机房1";
	}
	else if (str_time[0] == '2')
	{
		Room = "机房2";
	}
	else {
		Room = "机房3";
	}
	if (str_time[2] == '1')
	{
		Time = "周一";
	}
	else if (str_time[2] == '2')
	{
		Time = "周二";
	}
	else if (str_time[2] == '3')
	{
		Time = "周三";
	}
	else if (str_time[2] == '4')
	{
		Time = "周四";
	}
	else 
	{
		Time = "周五";
	}
	if (str_time[4] == '1')
	{
		SepTime = "上午";
	}
	else
	{
		SepTime = "下午";
	}
	if (str_time[6] == '0')
	{
		flag_Res = "预约审核中";
	}
	else if (str_time[6] == '1')
	{
		flag_Res = "预约审核通过";
	}
	else
	{
		flag_Res = "预约取消";
	}
	//cout << Room + " " + Time + " " + SepTime;
	return str_name+" "+ Room + " " + Time + " " + SepTime;
}
void Student::Show_oper()
{
	cout << "*************************************" << endl;
	cout << "**********1.申请预约******************" << endl;
	cout << "**********2.查看自身预约**************" << endl;
	cout << "**********3.查看所有预约**************" << endl;
	cout << "**********4.取消预约******************" << endl;
	cout << "**********0.注销登录******************" << endl;
	cout << "************************************" << endl;
}
void Student::reserve_Stu(map<int,string>& m_Order)
{
	int choice_room;
	cout << " choice the motor room you want reserve" << endl;
	cout << "no.1 capacity 20  no.2 capacity 50  no.3 capacity 100" << endl;
	cin >> choice_room;
	int choice_time;
	cout << " choice your order time" << endl;
	cout << "from Monday to Friday" << endl;
	cin >> choice_time;
	int choice_spetime;
	cout << " choice your order time in the morning or afternoon" << endl;
	cout << "1.morning  2.afternoon" << endl;
	cin >> choice_spetime;
	string Info_order = this->m_name + " " + to_string(choice_room) + " " + to_string(choice_time) + " " + to_string(choice_spetime)
		+ " " + to_string(FLAG_RES_ING);
	flag_Res = "预约审核中";
	//更新m_Order
	m_Order.erase(this->m_Account);
	m_Order.insert(make_pair(this->m_Account, Info_order));
	cout << "your order is successfully" << endl;
	save_order(m_Order);
}
void Student::exit_StuOpera()
{
	cout << "login successfully logged out" << endl;
	return;
}
void Student::CheckRes_self(map<int, string>& m_Order)
{
	//不存在预约信息
	if (m_Order.end() == m_Order.find(this->m_Account))
	{
		cout << "there is no reserve" << endl;
	}
	//存在预约信息
	cout << " 账号:" << this->m_Account << " 姓名:" << this->Get_Info(m_Order, this->m_Account) << " " <<flag_Res << endl;;
}
void Student::CheckRes_all(map<int, string>& m_Order)
{
	//不存在预约信息
	if (m_Order.size() == 0)
	{
		cout << "there is no reserve" << endl;
	}
	//存在预约信息
	for (auto it = m_Order.begin(); it != m_Order.end(); it++)
	{
		cout << " 账号:" << it->first << " 姓名:" << this->Get_Info(m_Order, it->first) << " " << flag_Res << endl;
	}
}
void Student::CancelRes(map<int, string>& m_Order)
{
	//不存在预约信息
	if (m_Order.end() == m_Order.find(this->m_Account))
	{
		cout << "there is no record" << endl;
	}
	//取消预约
	flag_Res = "预约取消";
	//复写m_Order
	auto it = m_Order.find(this->m_Account);
	it->second.replace(it->second.size() - 1, 1, to_string(FLAG_RES_CANCEL));//将文件最后一个数字替换成FLAG_RES_CANCEL，表示预约取消
	//重新保存文件
	save_order(m_Order);
	cout << "you cancel the reserve successfully" << endl;
}
void Student::save_order(map<int, string>& m_Order)
{
	ofstream ofs(PATH_ODER, ios::out);
	if (!ofs.is_open())
	{
		cout << "open the file error" << endl;
	}
	for (auto itt = m_Order.begin(); itt != m_Order.end(); ++itt)
	{
		ofs << itt->first << " " << itt->second << endl;
	}
	ofs.close();
}