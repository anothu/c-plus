// AMS.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include"billList.h"
#include"cardList.h"
#include"moneyList.h"
#include"global.h"
#include"menu.h"
#include"model.h"
#include"service.h"
#include"tool.h"
#include<iostream>
using namespace std;


int main()
{
	char selection; // 输入菜单项编号

	CardNode* pCardNodeHead = NULL;
	pCardNodeHead = CardListInit(CARDPATH);//读文件，创建card链表，返回表头

	BillingNode *pBillingNodeHead = NULL;
	pBillingNodeHead = BillListInit(BILLINGPATH);//读文件，创建bill链表，返回表头

	MoneyNode* pMoneyNodeHead = NULL;
	pMoneyNodeHead = MoneyListInit(MONEYPATH);//读文件，创建money链表，返回表头

	cout << endl;
	cout << "★欢迎进入计费管理系统★" << endl;
	cout << endl;
	do
	{
		outputMenu();
		selection = 'a'; // 初始化选择的菜单项编号为'a'
		cin >> selection; // 输入菜单项编号
		cin.clear();
		cin.sync();//清空缓冲流
		switch (selection) //选择的菜单编号
		{
		case '1'://添加卡
		{
			cout << endl << "-------添加卡--------" << endl << endl;
			addCard(&pCardNodeHead,&pMoneyNodeHead);
			break;
		}
		case '2': //查询卡
		{
			
			queryCard(pCardNodeHead);
			cout << endl << "-------查询卡--------" << endl << endl;
			break;
		}
		case '3'://上机
		{
			shangji(pCardNodeHead, &pBillingNodeHead);
			cout << endl << "-------上机----------" << endl << endl;
			break;
		}
		case '4': // 下机
		{
			xiaJi(pCardNodeHead, pBillingNodeHead);
			cout << endl << "-------下机----------" << endl << endl;
			break;
		}
		case '5'://充值
		{
			addMoney(pCardNodeHead, &pMoneyNodeHead);
			cout << endl << "-------充值----------" << endl << endl;
			break;
		}
		case '6'://退费
		{
			refundMoney(pCardNodeHead, &pMoneyNodeHead);
			cout << endl << "-------退费----------" << endl << endl;
			break;
		}
		case '7'://查询统计
		{
			statistics(pCardNodeHead, pBillingNodeHead, pMoneyNodeHead);
			cout << endl << "-----查询统计--------" << endl << endl;
			break;
		}
		case '8'://注销卡
		{
			logout(pCardNodeHead, &pMoneyNodeHead);
			cout << endl << "------注销卡---------" << endl << endl;
			break;
		}
		case '0': // 退出
		{
			clearData(pCardNodeHead);
			cout << endl << "谢谢你使用本系统！ " << endl << endl;
			break;
		}
		default:
		{
			cout << "输入的菜单编号错误！ \n";
			break;
		}
		}
		cout << endl;
	} while (selection != '0');

	return 0;
}
// 系统菜单

