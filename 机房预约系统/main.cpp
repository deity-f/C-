#include<iostream>
#include"ResManager.h"
using namespace std;

int main()
{
	ResManager RM;
	//RM.reserve_Stu();
	while (1)
	{
		RM.Show_reg();
		int choice = 0;
		cout << "choice your identity 1.Student 2.Teacher 3.Administrator enter '0' quit the system" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0://quit the system
			RM.Exitsystem();
			break;
		case 1://you choice Student
			RM.Oper(1);
			break;
		case 2://you choice Teacher
			RM.Oper(2);
			break;
		case 3://you choice Admin
			break;
		default://enter error,try again
			break;
		}
		system("pause");
		system("cls");
	}

	return 0;
}