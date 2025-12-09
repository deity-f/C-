#pragma once
#include"Person.h"
class Admin:public Person
{
public:
	Admin() {}
	Admin(string, int);
	void Show_oper();
};
