#include"stdafx.h"
#include <string>
#include <iostream>
#include"cardList.h"
#include"moneyList.h"
#include "menu.h"
#include"model.h"
#include "global.h"
#include"tool.h"
#include<fstream>
#include"billList.h"
#include"service.h"

using namespace std;

void addCard(CardNode** ppCardNodeHead,MoneyNode** ppMoneyNodeHead)
{
	string strNo;
	string strPwd;
	float fBalance;
	if (inputNoPwdBalance(strNo, strPwd, fBalance))//输入卡号，密码，金额
	{
		int nResult = addNewCard(strNo, strPwd, fBalance, ppCardNodeHead, ppMoneyNodeHead);//添加新卡
		switch (nResult)
		{
		case FINDCARD:
		{
			cout << endl << endl << "卡【 " << strNo << "】已经存在，添加新卡失败！ " << endl << endl;
			break;
		}
		case SUCCESS:
		{
			cout << endl << endl << "添加新卡成功!" << endl << endl;
			cout << "新卡卡号： " << strNo << endl;
			cout << "新卡金额： " << fBalance << endl;
			break;
		}
		default:
		{
			cout << endl << endl << "系统错误!" << endl << endl;
			break;
		}
		}
	}
	else
	{
		cout << endl << endl << "输入的【卡号，密码，金额】等信息格式不符号要求，			添加卡失败!" << endl << endl;
	}
}

void queryCard(CardNode* const pCardNodeHead)
{
	displayCard(pCardNodeHead);
}

void clearData(CardNode* pCardNodeHead)
{
	CardNode *pCardNode;
	while (pCardNodeHead != NULL)
	{
		pCardNode = pCardNodeHead;
		pCardNodeHead = pCardNodeHead->next;
		delete pCardNode;
	}//从链表表头开始删除链表
}

void logout(CardNode* pCardNodeHead, MoneyNode** ppMoneyNodeHead) {
	string strNo;
	string strPwd;

	MoneyInfo* pInfo = new MoneyInfo;

	if (inputNoPwd(strNo, strPwd)) {
		cout << "----------注销信息如下----------\n";

		int nResult = annulCard(strNo, strPwd, pInfo, pCardNodeHead, ppMoneyNodeHead);
		switch (nResult)
		{
		case NOFINDCARD:
		case NOMATCH:
			cout << endl << endl << "卡不存在，或卡信息不对，注销失败" << endl << endl;
			break;
		case SUCCESS:
			cout << endl;
			cout << "卡号: \t" << strNo << endl;;
			cout << "退款金额: \t" << pInfo->fMoney << endl;
			break;
		case USING:
			cout << endl << "该卡正在上机，不能注销！" << endl;
			break;
		case INVALID:
			cout << endl << "卡已经注销过了！";
			break;
		default:
			break;
		}
	}
	else {
		cout << endl << endl << "卡号或密码格式不正确，注销失败！" << endl << endl;
	}

	delete pInfo;

}

void statistics(CardNode* pCardNodeHead, BillingNode* pBillingNodeHead, MoneyNode* pMoneyNodeHead) {
	char selection;

	cout << endl;
	cout << "★欢迎进入查询统计系统★" << endl;
	cout << endl;

	do
	{
		outputStatisticsMenu();

		selection = 'a';
		cin >> selection;
		cin.ignore(1000, '\n'); //清空键盘缓冲流

		switch (selection)
		{
		case'1':
		{
			cout << endl << "-------卡号相关--------" << endl << endl;
			aboutCard(pCardNodeHead, pBillingNodeHead, pMoneyNodeHead);
			break;
		}
		case'2':
		{
			cout << endl << "-------上机下机相关--------" << endl << endl;
			searchBilling( pCardNodeHead, pBillingNodeHead);
			break;
		}
		case'3':
		{
			cout << endl << "-------充值退费相关--------" << endl << endl;
			aboutMoney(pCardNodeHead, pBillingNodeHead, pMoneyNodeHead);
			break;
		}
		case'0':
		{
			cout << endl << "完成查询统计工作！" << endl << endl;
			break;
		}
		default:
		{
			cout << "输入的编号错误！" << endl;
			break;
		}
		}
		cout << endl;
	} while (selection != '0');

}

void aboutCard(CardNode* pCardNodeHead, BillingNode* pBillingNodeHead, MoneyNode* pMoneyNodeHead) {
	cout << "----------卡号创建相关信息如下----------\n";

	string t0, t1;

	cout << endl << "请输入查询时间段(开始,如%d-%d-%d-%d:%d)：";
	cin >> t0;
	time_t tbegin = stringToTime(const_cast<char*>(t0.c_str()));//string为const char* 
	if (tbegin == -1) {
		cout << endl << "输入格式错误" << endl;
		return;
	}

	cout << endl << "请输入查询时间段(结束,如%d-%d-%d-%d:%d)：";
	cin >> t1;
	time_t tover = stringToTime(const_cast<char*>(t1.c_str()));
	if (tover == -1) {
		cout << endl << "输入格式错误" << endl;
		return;
	}

	CardNode* pCardNode = pCardNodeHead;
	char aStartTime[TIMELENGTH] = { 0 };
	char aEndTime[TIMELENGTH] = { 0 };
	int sum = 0;

	cout << endl << endl << "卡号\t开卡时间\t使用次数\t最后使用时间\t余额\n" << endl << endl;
	while (pCardNode != NULL)// 循环直到card检索完
	{
		if (pCardNode->data.tStart >= tbegin && pCardNode->data.tStart <= tover) //如果开卡时间在检索时间之间
		{
			timeToString(pCardNode->data.tStart, aStartTime);
			timeToString(pCardNode->data.tLast, aEndTime);
			cout << pCardNode->data.aName << "\t" << aStartTime << "\t"
				<< pCardNode->data.nUseCount << "\t" << aEndTime << "\t"
				<< pCardNode->data.fBalance << endl;
			sum++;//统计卡的张数
		}
		pCardNode = pCardNode->next;
	}
	cout << endl << endl << "总开卡张数为：" << sum << "张" << endl;
}

void aboutMoney(CardNode* pCardNodeHead, BillingNode* pBillingNodeHead, MoneyNode* pMoneyNodeHead) {
	cout << "----------充值退费相关信息如下----------\n";

	string t0, t1;

	cout << endl << "请输入查询时间段(开始,如%d-%d-%d-%d:%d)：";
	cin >> t0;
	time_t tbegin = stringToTime(const_cast<char*>(t0.c_str()));//string为const char* 
	if (tbegin == -1) {
		cout << endl << "输入格式错误" << endl;
		return;
	}

	cout << endl << "请输入查询时间段(结束,如%d-%d-%d-%d:%d)：";
	cin >> t1;
	time_t tover = stringToTime(const_cast<char*>(t1.c_str()));
	if (tover == -1) {
		cout << endl << "输入格式错误" << endl;
		return;
	}

	MoneyNode* pMoneyNode = pMoneyNodeHead;
	char aTime[TIMELENGTH] = { 0 };
	//char aEndTime[TIMELENGTH] = { 0 };
	float sum1 = 0;
	float sum2 = 0;

	cout << endl << endl << "卡号\t充值退费时间\t充值(0)或退费(1)\t充值退费金额\n" << endl << endl;
	while (pMoneyNode != NULL) {
		if (pMoneyNode->data.tTime >= tbegin && pMoneyNode->data.tTime <= tover) {
			timeToString(pMoneyNode->data.tTime, aTime);
			cout << pMoneyNode->data.aCardName << "\t" << aTime << "\t"
				<< pMoneyNode->data.nStatus << "\t\t" << pMoneyNode->data.fMoney << "\t" << endl;
			if (pMoneyNode->data.nStatus == 0) {
				sum1 += pMoneyNode->data.fMoney;
			}
			else {
				sum2 += pMoneyNode->data.fMoney;
			}
		}
		pMoneyNode = pMoneyNode->next;
	}
	cout << endl << endl << "总充值额为：" << sum1 << "元" << endl;
	cout << endl << endl << "总退费额为：" << sum2 << "元" << endl;
}





