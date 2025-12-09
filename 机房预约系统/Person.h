#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<memory>
using namespace std;
class Person
{
public:
	virtual ~Person() = 0;
	virtual void Show_oper() = 0;
	string m_name;
	int m_Account;
	int m_Core;
	string flag_Res;
};
