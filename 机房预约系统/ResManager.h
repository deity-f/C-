#pragma once
#include"Student.h"
#include"Teacher.h"
#include"Admin.h"
#include<string>
#include<vector>
#include<map>
#include<memory>
using namespace std;

class ResManager
{
public:
	ResManager();
	void Init();
	void LoadOrder();
	void LoadInfo();
	void Show_reg();//登录界面
	void Exitsystem();//quit the system
	bool Login(int choice);//Verify the info of enrollee
	//void Show_Sceond(int choice);//次级界面，与登陆者信息有关
	void Oper(int choice);//操作功能
	//void reserve_Stu();//预约机房

	shared_ptr<Person> ptr_per;
	map<int, string> m_Order;

	map<int, shared_ptr<Person>> vs_LO;//学生信息
	map<int, shared_ptr<Person>> vt_LO;//教师信息
	map<int, shared_ptr<Person>> va_LO;//管理员信息
	//vector<Student> v1;//一号机房 20
	//vector<Student> v2;//二号机房 50
	//vector<Student> v3;//三号机房 100
	map<int, vector<shared_ptr<Person>>> m1_t;//存储各个时间段1号机房学生信息
	map<int, vector<shared_ptr<Person>>> m2_t;//存储各个时间段2号机房学生信息
	map<int, vector<shared_ptr<Person>>> m3_t;//存储各个时间段3号机房学生信息
};
