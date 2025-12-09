#pragma once
#include"Person.h"
#include<map>

class Student :public Person
{
public:
	Student();
	Student(string, int, int);
	
	void Init();
	void Show_oper();
	void reserve_Stu(map<int,string>& m_Order);//预约机房
	void save_order(map<int, string>& m_Order);//保存预约信息
	void CheckRes_self(map<int, string>& m_Order);//查看自身预约
	string Get_Info(map<int, string>& m_Order,int index);//获取文件中预约信息
	void CheckRes_all(map<int, string>& m_Order);//查看所有预约
	void CancelRes(map<int, string>& m_Order);//取消预约
	void exit_StuOpera();

	
};
