#include"Teacher.h"
#include<map>
#include<algorithm>
#include<vector>
#include"Student.h"
#define FLAG_RES_CANCEL 3
#define FLAG_RES_PASS 1
#define FLAG_RES_ING 0
#define PATH_ODER "E:/C++/机房预约系统/order.txt"
#define PATH_ALL1 "E:/C++/机房预约系统/all1.txt"
#define PATH_ALL2 "E:/C++/机房预约系统/all2.txt"
#define PATH_ALL3 "E:/C++/机房预约系统/all3.txt"
Teacher::Teacher(string name,int account,int core)
{
	m_name = name;
	m_Account = account;
	m_Core = core;
}
void Teacher::Show_oper()
{
	cout << "*************************************" << endl;
	cout << "**********1.查看所有预约***************" << endl;
	cout << "**********2.审核预约******************" << endl;
	cout << "**********0.注销登录******************" << endl;
	cout << "************************************" << endl;
}
string Teacher::Get_Info(map<int, string>& m_Order, int index)
{
	int count = 0;
	int pos = 0;
	string str_time;
	string Room;
	string Time;
	string SepTime;
	string str_name;
	string str_info = m_Order[index];
	for (auto it = str_info.begin(); it != str_info.end(); it++, pos++)//获取到order文件中关于时间的信息，后三个数
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
	return str_name + " " + Room + " " + Time + " " + SepTime;
}
void Teacher::CheckRes_all(map<int, string>& m_Order)
{
	//不存在预约信息
	if (m_Order.size() == 0)
	{
		cout << "there is no reserve" << endl;
	}
	//存在预约信息
	for (auto it = m_Order.begin(); it != m_Order.end(); it++)
	{
		cout << " 账号:" << it->first << " 姓名:" << this->Get_Info(m_Order, it->first) << " " << flag_Res << endl;;
	}
}
void Teacher::VerifyRes(map<int, string>& m_Order,map<int, vector<shared_ptr<Person>>>& m1_t, map<int, vector<shared_ptr<Person>>>& m2_t, map<int, vector<shared_ptr<Person>>>& m3_t, map<int, shared_ptr<Person>>& vs_LO)
{
	//不存在预约信息
	if (m_Order.size() == 0)
	{
		cout << "there is no reserve" << endl;
	}
	//找到申请预约
	while (1)
	{
		int count = 0;
		for (auto it = m_Order.begin(); it != m_Order.end(); ++it)
		{
			if (*(it->second.end() - 1) == '0')//找到正在审核中的记录
			{
				count++;
				cout << "no." << count << " 账号:" << it->first << " 姓名:" << this->Get_Info(m_Order, it->first) << " " << flag_Res << endl;
				
			}

		}
		if (count == 0)
		{
			cout << "no record" << endl;
		}
		cout << "choice the account you want to pass,enter 0 quit" << endl;
		int choice_ver;//学号
		cin >> choice_ver;
		if (choice_ver == 0)
		{
			return;
		}
		m_Order[choice_ver].replace(m_Order[choice_ver].size() - 1, 1, to_string(FLAG_RES_PASS));
		//更新到m_Order
		save_order(m_Order);
		//保存到mx_t
		for (auto it = m_Order.begin(); it != m_Order.end(); ++it)
		{
			if (*(it->second.end() - 1) == '1' && *(it->second.end() - 7) == '1')//找到审核通过学生，1号机房
			{
				Allocation(m_Order, it->first, m1_t, vs_LO);
				save_al(m1_t,1);
			}
			if (*(it->second.end() - 1) == '1' && *(it->second.end() - 7) == '2')
			{
				Allocation(m_Order, it->first, m2_t, vs_LO);
				save_al(m2_t,2);
			}
			if (*(it->second.end() - 1) == '1' && *(it->second.end() - 7) == '3')
			{
				Allocation(m_Order, it->first, m3_t, vs_LO);
				save_al(m3_t,3);
			}
		}
		cout << "verify successfully" << endl;
		system("pause");
		system("cls");
		this->Show_oper();
	}

}
void Teacher::save_order(map<int, string>& m_Order)
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
void Teacher::Allocation(map<int, string>& m_Order, int index, map<int, vector<shared_ptr<Person>>>& m, map<int, shared_ptr<Person>>& vs_LO)
{
	int count = 0;
	int pos = 0;
	string str_time;
	int Time;
	int SepTime;
	string str_name;
	string str_info = m_Order[index];//所需处理的请求信息
	for (auto it = str_info.begin(); it != str_info.end(); it++, pos++)//获取到order文件中关于时间的信息，后三个数
	{
		if (*it == ' ')
		{
			count++;
		}
		if (count >= 1 && *it != ' ')
		{
			str_time = str_info.substr(pos, str_info.size() - pos); //Room + " " + Time + " " + SepTime;
			break;
		}
	}

	Time = str_time[2] - '0';
	SepTime = str_time[4] - '0';
	vector<shared_ptr<Person>> v;
	v.push_back(vs_LO[index]);
	m.insert(make_pair(Time * 10 + SepTime, v));//vs_LO[index]为指向学生信息的指针,第一个参数为时间信息，第二个为机房信息，机房储存的为学生信息。

}
void Teacher::save_al(map<int, vector<shared_ptr<Person>>>& m,int i)
{
	if (i == 1)
	{
		ofstream ofs(PATH_ALL1, ios::out);
		if (!ofs.is_open())
		{
			cout << "open error" << endl;
		}
		for (auto it = m.begin(); it != m.end(); ++it)
		{
			vector<shared_ptr<Person>> v = it->second;
			int time = it->first;
			string septime;
			if (time % 10 == 1)
			{
				septime = "上午";
			}
			else
			{
				septime = "下午";
			}
			for (auto itt = v.begin(); itt != v.end(); ++itt)
			{
				ofs << "机房" << i << " 周" << time / 10 << " " << septime;
				ofs << (*itt)->m_Account << " " << (*itt)->m_name << endl;
			}
			//ofs << it->first << endl;
		}
		ofs.close();
	}
	else if (i == 2)
	{
		ofstream ofs(PATH_ALL2, ios::out);
		if (!ofs.is_open())
		{
			cout << "open error" << endl;
		}
		for (auto it = m.begin(); it != m.end(); ++it)
		{
			vector<shared_ptr<Person>> v = it->second;
			int time = it->first;
			string septime;
			if (time % 10 == 1)
			{
				septime = "上午";
			}
			else
			{
				septime = "下午";
			}
			for (auto itt = v.begin(); itt != v.end(); ++itt)
			{
				ofs << "机房" << i << " 周" << time / 10 << " " << septime;
				ofs << (*itt)->m_Account << " " << (*itt)->m_name << endl;
			}
			//ofs << it->first << endl;
		}
		ofs.close();
	}
	else
	{
		ofstream ofs(PATH_ALL3, ios::out);
		if (!ofs.is_open())
		{
			cout << "open error" << endl;
		}
		for (auto it = m.begin(); it != m.end(); ++it)
		{
			vector<shared_ptr<Person>> v = it->second;
			int time = it->first;
			string septime;
			if (time % 10 == 1)
			{
				septime = "上午";
			}
			else
			{
				septime = "下午";
			}
			for (auto itt = v.begin(); itt != v.end(); ++itt)
			{
				ofs << "机房" << i << " 周" << time / 10 << " " << septime;
				ofs << (*itt)->m_Account << " " << (*itt)->m_name << endl;
			}
			//ofs << it->first << endl;
		}
		ofs.close();
	}
	
}
	
