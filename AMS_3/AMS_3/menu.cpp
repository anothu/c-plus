#include "stdafx.h"
#include <string>
#include"cardList.h"
#include<iostream>
#include"global.h"
#include"model.h"
#include"tool.h"

using namespace std;

void outputStatisticsMenu(){
	cout << "--------查询统计菜单--------" << endl << endl;
	cout << "1.卡号相关" << endl;
	cout << "2.上机下机相关" << endl;
	cout << "3.充值退费相关" << endl;
	cout << "0.退出" << endl << endl;
	cout << "请选择菜单项编号（0~3）：";
}

void outputMenu()
{

	cout << "---------计费系统菜单---------" << endl << endl;
	cout << "1.添加卡" << endl;
	cout << "2.查询卡" << endl;
	cout << "3.上机" << endl;
	cout << "4.下机" << endl;
	cout << "5.充值" << endl;
	cout << "6.退费" << endl;
	cout << "7.查询统计" << endl;
	cout << "8.注销卡" << endl;
	cout << "0.退出" << endl << endl;

	cout << "请选择菜单项编号（0~8）：";

}

bool inputCardNo(string& strNo)
{

	while (true)
	{
		cout << "请输入卡号（长度为1~17）：";
		cin >> strNo;
		cin.clear();
		cin.sync();
		if (strNo.length() >= 17)
		{
			cout << "卡号长度超过最大值！" << endl;

			char ch = 'M';
			while (ch != 'N'&&ch != 'Y')
			{
				cout << "重新输入吗？（y/n）";
				cin >> ch;
				ch = toupper(ch);
				cin.ignore(1000, '\n');
			}
			if (ch == 'N')
			{
				return false;
			}
		}
		else
		{
			break;
		}
	}
}

bool inputCardPwd(string& strPwd)
{

	while (true)
	{
		cout << "请输入密码：";
		cin >> strPwd;
		if (strPwd.length() <= 6)
		{
			cout << "密码不能少于六位" << endl;
			char ch = 'M';
			while (ch != 'N'&&ch != 'Y')
			{
				cout << "重新输入吗？（y/n）";
				cin >> ch;
				ch = toupper(ch);
				cin.ignore(1000, '\n');
			}

			if (ch == 'N')
			{
				return false;
			}
		}
		else
		{
			break;
		}
	}
}

bool inputCardBalance(float& fbalance)
{

	while (true)
	{
		cout << "请输入金额：";
		cin >> fbalance;
		if (fbalance <3)
		{
			cout << "金额不能小于三元" << endl;
			char ch = 'M';
			while (ch != 'N'&&ch != 'Y')
			{
				cout << "重新输入吗？（y/n）";
				cin >> ch;
				ch = toupper(ch);
				cin.ignore(1000, '\n');
			}
			if (ch == 'N')
			{
				return false;
			}
		}
		else
		{
			break;
		}
	}
}

bool inputNoPwd(string& strNo, string& strPwd)
{
	if (!inputCardNo(strNo))
	{
		return false;
	}
	if (!inputCardPwd(strPwd))
	{
		return false;
	}
	return true;
}

bool inputNoPwdBalance(string& strNo, string& strPwd, float& fBalance)
{

	if (!inputCardNo(strNo))
	{
		return false;
	}
	if (!inputCardPwd(strPwd))
	{
		return false;
	}
	if (!inputCardBalance(fBalance))
	{
		return false;
	}

	return true;
}

