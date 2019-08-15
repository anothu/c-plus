
#include "stdafx.h"
#include"menu.h"
#include"tool.h"
#include"service.h"
#include<iostream>
#include"model.h"
#include <string> 
#include <stdio.h>
#include "global.h"
#include<fstream>
#include"cardList.h"
#include"billList.h"
using namespace std;

MoneyNode* MoneyListInit(const string billingFilename)
{
	ifstream moneyfile(billingFilename);
	MoneyNode *pMoneyNode, *pMoneyNodeHead, *pMoneyNodeTail;
	Money money;
	if (!moneyfile.is_open())
	{
		return NULL;
	}
	pMoneyNodeHead = NULL;
	pMoneyNodeTail = NULL;
	while (1)
	{
		moneyfile.read((char*)&money, sizeof(Money));
		if (moneyfile.eof())
		{
			break;
		}
		pMoneyNode = new MoneyNode;
		pMoneyNode->data = money;
		if (pMoneyNodeHead == NULL)
		{
			pMoneyNodeHead = pMoneyNode;
			pMoneyNodeTail = pMoneyNode;
		}
		else
		{
			pMoneyNodeTail->next = pMoneyNode;
			pMoneyNodeTail = pMoneyNodeTail->next;
		}
	}
	pMoneyNodeTail->next = NULL;

	moneyfile.close();

	return pMoneyNodeHead;
}//读文件，创建money链表，返回表头

bool saveMoney(const Money* pBill, const string pPath)
{
	ofstream ofile(pPath, ios::binary | ios::app);
	ofile.write((char*)pBill, sizeof(Money));
	ofile.close();
	return true;
}

int recharge(string strNo, string strPwd, float fMoney, MoneyInfo* pInfo, CardNode* pCardNodeHead, MoneyNode** ppMoneyNodeHead) {
	Money money;
	int nCardIndex;
	Card *pCard = cardIsExist(strNo, nCardIndex, pCardNodeHead);

	if (pCard == NULL) {
		return NOFINDCARD;
	}

	if (strcmp(pCard->aPwd, strPwd.c_str()) != 0) {
		return NOMATCH;
	}

	if (pCard->nStatus == INVALID) {
		return INVALID;
	}

	pCard->fBalance += fMoney;
	pCard->fTotalUse += fMoney;

	//更新文件中的卡信息
	updateCard(pCard, CARDPATH, nCardIndex);
	strcpy_s(money.aCardName, strNo.c_str());
	money.tTime = time(NULL);
	money.nStatus = 0;
	money.fMoney = fMoney;
	money.nDel = 0;

	saveMoney(&money, MONEYPATH);//保存money信息在dat中

	MoneyNode *pMoneyNode = new MoneyNode;
	pMoneyNode->data = money;
	MoneyNode* pMoneyNodeTail = *ppMoneyNodeHead;

	if (*ppMoneyNodeHead == NULL) {
		*ppMoneyNodeHead = pMoneyNode;
		pMoneyNodeTail = pMoneyNode;
	}
	else {
		while (pMoneyNodeTail->next != NULL) {
			pMoneyNodeTail = pMoneyNodeTail->next;
		}
		pMoneyNodeTail->next = pMoneyNode;
		pMoneyNodeTail = pMoneyNodeTail->next;
	}
	pMoneyNodeTail->next = NULL;
	//将信息保存在pinfo中
	strcpy_s(pInfo->aCardName, strNo.c_str());
	pInfo->fMoney = money.fMoney;
	pInfo->fBalance = pCard->fBalance;

	return SUCCESS;
}

int returnMoney(string strNo, string strPwd, MoneyInfo* pInfo, CardNode* pCardNodeHead, MoneyNode** ppMoneyNodeHead) {
	Money money;
	int nCardIndex;
	Card *pCard = cardIsExist(strNo, nCardIndex, pCardNodeHead);

	if (pCard == NULL) {
		return NOFINDCARD;
	}

	if (strcmp(pCard->aPwd, strPwd.c_str()) != 0) {
		return NOMATCH;
	}

	if (pCard->nStatus == INVALID) {
		return INVALID;
	}

	if (pCard->nStatus == USING) {
		return USING;
	}

	strcpy_s(money.aCardName, strNo.c_str());
	money.tTime = time(NULL);
	money.nStatus = 1;
	money.fMoney = pCard->fBalance;
	money.nDel = 0;

	saveMoney(&money, MONEYPATH);

	MoneyNode *pMoneyNode = new MoneyNode;
	pMoneyNode->data = money;

	MoneyNode* pMoneyNodeHead = *ppMoneyNodeHead;
	MoneyNode* pMoneyNodeTail = *ppMoneyNodeHead;

	if (pMoneyNodeHead == NULL) {
		pMoneyNodeHead = pMoneyNode;
		pMoneyNodeTail = pMoneyNode;
	}
	else {
		while (pMoneyNodeTail->next != NULL) {
			pMoneyNodeTail = pMoneyNodeTail->next;
		}
		pMoneyNodeTail->next = pMoneyNode;
		pMoneyNodeTail = pMoneyNodeTail->next;
	}
	pMoneyNodeTail->next = NULL;

	pCard->fBalance = 0;
	pCard->fTotalUse -= money.fMoney;

	//更新文件中的卡信息
	updateCard(pCard, CARDPATH, nCardIndex);

	strcpy_s(pInfo->aCardName, strNo.c_str());
	pInfo->fMoney = money.fMoney;
	pInfo->fBalance = pCard->fBalance;

	return SUCCESS;
}

void addMoney(CardNode* pCardNodeHead, MoneyNode** ppMoneyNodeHead) {
	string strNo;
	string strPwd;
	float fMoney;

	MoneyInfo* pInfo = new MoneyInfo;

	if (inputNoPwdBalance(strNo, strPwd, fMoney)) {
		cout << "----------充值信息如下----------\n";

		int nResult = recharge(strNo, strPwd, fMoney, pInfo, pCardNodeHead, ppMoneyNodeHead);
		switch (nResult)
		{
		case NOFINDCARD:
		case NOMATCH:
			cout << endl << endl << "卡不存在，或卡信息不对，充值失败" << endl << endl;
			break;
		case SUCCESS:
			cout << endl;
			cout << "卡号: \t" << strNo << endl;;
			cout << "充值金额: \t" << pInfo->fMoney << endl;
			cout << "余额：\t" << pInfo->fBalance << endl;
			break;
		case INVALID:
			cout << endl << "该卡已注销，不能充值！" << endl;
			break;
		default:
			break;
		}
	}
	else {
		cout << endl << endl << "卡号或密码格式不正确，充值失败！" << endl << endl;
	}

	delete pInfo;

}

void refundMoney(CardNode* pCardNodeHead, MoneyNode** ppMoneyNodeHead) {
	string strNo;
	string strPwd;

	MoneyInfo* pInfo = new MoneyInfo;

	if (inputNoPwd(strNo, strPwd)) {
		cout << "----------退费信息如下----------\n";

		int nResult = returnMoney(strNo, strPwd, pInfo, pCardNodeHead, ppMoneyNodeHead);
		switch (nResult)
		{
		case NOFINDCARD:
		case NOMATCH:
			cout << endl << endl << "卡不存在，或卡信息不对，退费失败" << endl << endl;
			break;
		case SUCCESS:

			cout << endl;
			cout << "卡号: \t" << strNo << endl;;
			cout << "退费金额: \t" << pInfo->fMoney << endl;
			cout << "余额：\t" << pInfo->fBalance << endl;

			break;
		case INVALID:
			cout << endl << "该卡已注销，不能退费！" << endl;
			break;
		case USING:
			cout << endl << "该卡正在上机，不能退费！" << endl;
			break;
		default:
			break;
		}
	}
	else {
		cout << endl << endl << "卡号或密码格式不正确，退费失败！" << endl << endl;
	}

	delete pInfo;

}

int annulCard(string strNo, string strPwd, MoneyInfo* pInfo, CardNode* pCardNodeHead, MoneyNode** ppMoneyNodeHead) {
	Money money;
	int nCardIndex;
	Card *pCard = cardIsExist(strNo, nCardIndex, pCardNodeHead);

	if (pCard == NULL) {
		return NOFINDCARD;
	}

	if (strcmp(pCard->aPwd, strPwd.c_str()) != 0) {
		return NOMATCH;
	}

	if (pCard->nStatus == USING) {
		return USING;
	}

	if (pCard->nStatus == INVALID) {
		return INVALID;
	}

	//更新money信息
	strcpy_s(money.aCardName, strNo.c_str());
	money.tTime = time(NULL);
	money.nStatus = 1;
	money.fMoney = pCard->fBalance;
	money.nDel = 0;



	//储存信息到dat
	saveMoney(&money, MONEYPATH);



	//用链表储存这条信息
	MoneyNode *pMoneyNode = new MoneyNode;
	pMoneyNode->data = money;
	MoneyNode* pMoneyNodeHead = *ppMoneyNodeHead;
	MoneyNode* pMoneyNodeTail = *ppMoneyNodeHead;
	if (pMoneyNodeHead == NULL) {
		pMoneyNodeHead = pMoneyNode;
		pMoneyNodeTail = pMoneyNode;
	}
	else {
		while (pMoneyNodeTail->next != NULL) {
			pMoneyNodeTail = pMoneyNodeTail->next;
		}
		pMoneyNodeTail->next = pMoneyNode;
		pMoneyNodeTail = pMoneyNodeTail->next;
	}
	pMoneyNodeTail->next = NULL;


	//更新文件中的卡信息
	pCard->fBalance = 0;
	pCard->nStatus = INVALID;
	updateCard(pCard, CARDPATH, nCardIndex);


	strcpy_s(pInfo->aCardName, strNo.c_str());
	pInfo->fMoney = money.fMoney;
	pInfo->fBalance = pCard->fBalance;

	return SUCCESS;
}//销卡