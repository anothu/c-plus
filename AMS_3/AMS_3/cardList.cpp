#include "stdafx.h"
#include"menu.h"
#include"tool.h"
#include"service.h"
#include<iostream>
#include"model.h"
#include <string> 
#include "global.h"
#include<fstream>
#include"moneyList.h"
#include"cardList.h"

using namespace std;

Card* cardIsExist(string strNo, int &nCardIndex, CardNode* const pCardNodeHead)
{
	CardNode *pCardNode = pCardNodeHead;
	nCardIndex = 0;
	while (pCardNode != NULL)//当链表中有card时
	{
		if (strcmp(pCardNode->data.aName, strNo.c_str()) == 0)
		{
			return &(pCardNode->data);//如果找到卡号符合的卡，返回它
		}
		pCardNode = pCardNode->next;//否则找下一张卡
		nCardIndex++;
	}
	return NULL;//若无符合的卡，返回NULL
}

bool saveCard(const Card* pCard, const string pPath)
{
	ofstream ofile(pPath, ios::binary | ios::app);
	ofile.write((char*)pCard, sizeof(Card));
	ofile.close();
	return true;
}//将card写入指定文件中

int addNewCard(string strNo, string strPwd, float fBalance, CardNode** ppCardNodeHead, MoneyNode** ppMoneyNodeHead)
{
	int nCardIndex = 0;
	if (cardIsExist(strNo, nCardIndex, *ppCardNodeHead) != NULL)
	{
		return FINDCARD;
	}
	Card card;
	strcpy(card.aName, strNo.c_str());//储存新卡账号
	strcpy(card.aPwd, strPwd.c_str());//储存新卡密码
	card.fBalance = fBalance;// 添加新卡时，累计金额等于开卡金额
	card.fTotalUse = card.fBalance;
	card.nStatus = UNUSE; // 卡状态
	card.nUseCount = 0; // 使用次数			
	card.tStart = card.tLast = time(NULL);// 开卡时间，最后使用时间都默认为当前时间
	CardNode* pCardNode = new CardNode;
	pCardNode->data = card;
	CardNode *pCardNodeHead = *ppCardNodeHead;//ppCardNodeHead是指向pCardNode的指针
	CardNode *pCardNodeTail = *ppCardNodeHead;
	if (pCardNodeHead == NULL)
	{
		// 第一张卡，通过ppCardNodeHead将表态指针返回
		pCardNodeHead = pCardNode;
		pCardNodeTail = pCardNode;
		*ppCardNodeHead = pCardNode;
	}
	else
	{
		//不是第一张卡，接在表尾
		pCardNodeTail = pCardNodeHead;
		while (pCardNodeTail->next != NULL)
			pCardNodeTail = pCardNodeTail->next;
		pCardNodeTail->next = pCardNode;
		pCardNodeTail = pCardNode;
	}
	pCardNodeTail->next = NULL;//将表尾设为空

	//**********
	Money money;
	strcpy_s(money.aCardName, strNo.c_str());
	money.tTime = time(NULL);
	money.nStatus = 0;
	money.fMoney = fBalance;
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
    //**********
	saveCard(&card, CARDPATH);//储存卡的信息
	return SUCCESS;
}

CardNode* CardListInit(const string cardFilename)
{
	ifstream cardfile(cardFilename);
	CardNode *pCardNode, *pCardNodeHead, *pCardNodeTail;
	Card card;
	if (!cardfile.is_open())
	{
		return NULL;
	}
	pCardNodeHead = NULL;
	pCardNodeTail = NULL;
	while (1)
	{
		cardfile.read((char*)&card, sizeof(Card));
		if (cardfile.eof())
		{
			break;
		}//当文件读完后退出
		pCardNode = new CardNode;
		pCardNode->data = card;
		if (pCardNodeHead == NULL)//第一张卡
		{
			pCardNodeHead = pCardNode;
			pCardNodeTail = pCardNode;
		}
		else//后面的卡
		{
			pCardNodeTail->next = pCardNode;
			pCardNodeTail = pCardNode;
		}
	}
	pCardNodeTail->next = NULL;//将表尾设为空
	cardfile.close();
	return pCardNodeHead;
}

void displayCard(CardNode* pCardNodeHead)
{
	if (pCardNodeHead == NULL)
	{
		cout << endl << endl << "一张上机卡都没有！ " << endl << endl;
		return;
	}

	string t;
	cout << "请输入查询的号码：";
	cin >> t;
	cout << "卡号\t状态\t余额\t累计使用\t使用次数\t上次使用时间" << endl;
	CardNode* pCur = pCardNodeHead;

	char buf[18];
	strcpy(buf, t.c_str());
	while (pCur != NULL)//当链表没有检索完
	{
		char aLastTime[TIMELENGTH] = { 0 };
		timeToString((pCur->data).tLast, aLastTime);//将时间格式化
		if (strncmp(buf, pCur->data.aName, t.length()) == 0)
		{
			cout << pCur->data.aName << "\t";
			if (pCur->data.nStatus == USING)
				cout << "上机\t";
			else if (pCur->data.nStatus == UNUSE)
				cout << "未上机\t";
			else if (pCur->data.nStatus == INVALID)
				cout << "注销\t";
			else
				cout << "错误\t";

			cout << pCur->data.fBalance << "\t";
			cout << pCur->data.fTotalUse << "\t\t" << pCur->data.nUseCount << "\t\t" << aLastTime << endl;
		}
		pCur = pCur->next;//检索下一张卡
	}
}