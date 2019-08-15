#include<iostream>
#include <iomanip>
#include<fstream>
#include"student.h"
using namespace std;
void smallmenu()
{
	cout << "1.按姓名查找" << endl;
	cout << "2.按学号查找" << endl;
	cout << "请输入你的选择:";
}
void menu()
{
	cout << "1.输入数据" << endl;
	cout << "2.输出数据" << endl;
	cout << "3.按姓名或者学号查找学生数据" << endl;
	cout << "4.退出" << endl;
};
void input(int n, student s[])
{
	ofstream f1("stud.dat", ios::binary || ios_base::out || ios::app);//ofstream ofile(pPath,ios_base::out|ios_base::app|ios_base::binary);
	int i;
	if (!f1.is_open())
	{
		cerr << "文件无法正确打开!不能写入计费系统!" << endl;
		f1.close();
		return;
	}
	for (i = 0; i<n; i++)
	{
		char nu[10];
		cout << "请输入第" << i + 1 << "个学生的学号";
		cin >> nu;
		for (int t = 0; t<10; t++)
		{
			s[i].num[t] = nu[t];
		}
		cout << "请输入第" << i + 1 << "个学生的姓名";
		cin >> s[i].name;
		cout << "请输入第" << i + 1 << "个学生的成绩";
		cin >> s[i].grade;
		f1 << s[i].num << " ";
		f1 << s[i].name << " ";
		f1 << s[i].grade << " ";
	}
	f1.close();
}
void output(int n, student s[])
{
	ifstream f1("stud.dat", ios::binary || ios_base::in);
	int i;
	cout << "学号" << "   " << "姓名" << "    " << "成绩" << endl;
	for (i = 0; i < n; i++)
	{
		char nu[10];
		f1 >> nu;
		for (int t = 0; t < 10; t++)
		{
			s[i].num[t] = nu[t];
		}
		f1 >> s[i].name;
		f1 >> s[i].grade;
		cout << s[i].num << "   ";
		cout << s[i].name << "   ";
		cout << s[i].grade << "   ";
		cout << endl;
	}
}
void save(int n, student s[])
{
	ifstream f1("stud.dat", ios::binary || ios_base::in);
	int i;
	for (i = 0; i < n; i++)
	{
		char nu[10];
		f1 >> nu;
		for (int t = 0; t < 10; t++)
		{
			s[i].num[t] = nu[t];
		}
		f1 >> s[i].name;
		f1 >> s[i].grade;
	}
}
bool equal(char a1[], char a2[], int length)
{
	for (int i = 0; i < length; i++)
		if (a1[i] != a2[i])
			return false;
	return true;
}
void searchbynum(int n, student s[])
{
	save(n, s);
	int i;
	char now_num[10];
	cout << "请输入要查询的学生的学号:";
	cin >> now_num;
	for (i = 0; i < n; i++)
	{
		if (strcmp(s[i].num, now_num) == 0)
			break;
	}
	cout << "学号" << "   " << "姓名" << "    " << "成绩" << endl;
	cout << s[i].num << "   ";
	cout << s[i].name << "   ";
	cout << s[i].grade << "   ";
	cout << endl;
}
void searchbyname(int n, student s[])
{
	save(n, s);
	char now_name[10];
	int length, i, j;
	cout << "请输入要查询的学生的姓名:";
	cin >> now_name;
	length = strlen(now_name);
	cout << "学号" << "   " << "姓名" << "    " << "成绩" << endl;
	for (i = 0; i<n; i++)
	{
		if (equal(now_name, s[i].name, length))
		{
			cout << s[i].num << "   ";
			cout << s[i].name << "   ";
			cout << s[i].grade << "   ";
			cout << endl;
		}
	}
}
void search(int n, student s[])
{
	int choice;
	smallmenu();
	cin >> choice;
	if (choice == 1)
		searchbyname(n, s);
	else if (choice == 2)
		searchbynum(n, s);
	else 
		cout << "输入选择错误!" << endl;
}