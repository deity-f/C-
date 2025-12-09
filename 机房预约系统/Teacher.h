#pragma once
#include<map>
#include<vector>
#include"Person.h"
class Teacher :public Person
{
public:
	Teacher() {}
	Teacher(string, int, int);
	void Show_oper();
	string Get_Info(map<int, string>& m_Order, int index);//获取文件中预约信息
	void CheckRes_all(map<int, string>& m_Order);//查看所有预约
	void VerifyRes(map<int, string>& m_Order, map<int, vector<shared_ptr<Person>>>& m1_t, map<int, vector<shared_ptr<Person>>>& m2_t, map<int, vector<shared_ptr<Person>>>& m3_t, map<int, shared_ptr<Person>>& vs_LO);//审核预约
	void save_order(map<int, string>& m_Order);//保存预约信息
	void Allocation(map<int, string>& m_Order, int index, map<int, vector<shared_ptr<Person>>>& m, map<int, shared_ptr<Person>>& vs_LO);//机房分配
	void save_al(map<int, vector<shared_ptr<Person>>>& m,int i);
};
