
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

BillingNode* BillListInit(const string billingFilename)
{
	ifstream billingfile(billingFilename);
	BillingNode *pBillingNode, *pBillingNodeHead, *pBillingNodeTail;
	Billing billing;
	if (!billingfile.is_open())
	{
		return NULL;
	}
	pBillingNodeHead = NULL;
	pBillingNodeTail = NULL;
	while (1)
	{
		billingfile.read((char*)&billing, sizeof(Billing));
		if (billingfile.eof())
		{
			break;
		}//读到文件末尾时退出循环
		pBillingNode = new BillingNode;
		pBillingNode->data = billing;
		if (pBillingNodeHead == NULL)
		{
			pBillingNodeHead = pBillingNode;
			pBillingNodeTail = pBillingNode;
		}
		else
		{
			pBillingNodeTail->next = pBillingNode;
			pBillingNodeTail = pBillingNode;
		}
	}
	pBillingNodeTail->next = NULL;
	billingfile.close();
	return pBillingNodeHead;
}//创建链表，返回表头

int logon(string strNo, string strPwd, LogonInfo* pInfo, CardNode* pCardNodeHead,BillingNode **ppBillingNodeHead)
{
	Billing billing; // 计费信息
	int nCardIndex;//用于写文件时定位
	Card* pCard = cardIsExist(strNo, nCardIndex, pCardNodeHead);//查找与卡号相符的卡
	if (pCard == NULL)
		return NOFINDCARD; // 未找到卡
	if (strcmp(pCard->aPwd, strPwd.c_str()) != 0)
		return NOMATCH; // 密码不匹配
	if (pCard->nStatus == USING)
	{
		return USING; // 卡正在上机
	}
	if (pCard->nStatus == INVALID)
	{
		return INVALID; // 卡已经注销
	}
	if (pCard->fBalance <= 0)
	{
		return ENOUGHMONEY; // 卡的余额为0
	}
	// 如果可以上机，更新卡信息
	pCard->nStatus = USING; // 状态为正在使用
	pCard->nUseCount++; // 使用次数加1
	pCard->tLast = time(NULL); // 更新最后使用时间为当前时间
    // 更新文件中的卡信息
	updateCard(pCard, CARDPATH, nCardIndex);
	// 添加消费记录
	strcpy(billing.aCardName, strNo.c_str()); // 上机卡号
	billing.tStart = time(NULL); // 上机时间
	billing.tEnd = 0; // 下机时间
	billing.nStatus = NOSETTLEMENT; // 消费状态
	billing.fAmount = 0; // 消费金额
						 // 先将计费信息保存到文件中
	saveBilling(&billing, BILLINGPATH);
	// 在计费链表中增加一条计费信息
	BillingNode* pBillingNode = new BillingNode;
	pBillingNode->data = billing;
	BillingNode* pBillingNodeTail = *ppBillingNodeHead;
	//当表中没有bill
	if (*ppBillingNodeHead == NULL)
	{
		*ppBillingNodeHead = pBillingNode;
		pBillingNodeTail = pBillingNode;
	}
	else//插入表尾
	{
		while (pBillingNodeTail->next != NULL)
			pBillingNodeTail = pBillingNodeTail->next;
		pBillingNodeTail->next = pBillingNode;
		pBillingNodeTail = pBillingNode;
	}
	pBillingNodeTail->next = NULL;
	// 组装上机信息
	strcpy(pInfo->aCardName, strNo.c_str());
	pInfo->fBalance = pCard->fBalance;
	pInfo->tLogon = billing.tStart;
	return SUCCESS;
}

bool updateCard(const Card* pCard, const string pPath, int nCardIndex)
{
	fstream ofile;
	ofile.open(pPath, ios_base::in | ios_base::out);
	ofile.seekp(sizeof(Card)*nCardIndex, ios_base::beg);//ncardindex用以定位
	ofile.write((char*)pCard, sizeof(Card));
	ofile.close();
	return true;
}

bool saveBilling(const Billing* pBill, const string pPath)
{
	ofstream ofile(pPath, ios::binary | ios::app);
	ofile.write((char*)pBill, sizeof(Billing));
	ofile.close();
	return true;
}

void shangji(CardNode* pCardNodeHead, BillingNode **ppBillingNodeHead)
{
	string strNo;
	string strPwd;
	LogonInfo* pInfo = new LogonInfo; // 上机信息，用于显示
	char aTime[TIMELENGTH] = { 0 }; // 上机时间，用于显示
	if (inputNoPwd(strNo, strPwd))//输入账号，密码
	{
		cout << endl << "----------上机信息----------" << endl;
		// 根据上机结果，提示不同信息
		int nResult = logon(strNo, strPwd, pInfo, pCardNodeHead,ppBillingNodeHead);//实现上机或者返回异常状态
		switch (nResult)
		{
		case NOFINDCARD:
		case NOMATCH:
		{
			cout << endl << endl << "卡不存在，或卡信息不对，不能上机！ " <<
				endl << endl;
			break;
		}
		case SUCCESS:
		{
			timeToString(pInfo->tLogon, aTime);
			cout << endl;
			cout << "卡号: \t" << strNo << endl;
			cout << "余额: \t" << pInfo->fBalance << endl;
			cout << "上机时间： \t" << aTime << endl;
			break;
		}
		case USING:
		{
			cout << endl << "该卡正在使用，不能重复上机！ " << endl;
			break;
		}
		case INVALID:
		{
			cout << endl << "该卡已注销，不能上机！ " << endl;
			break;
		}
		case ENOUGHMONEY:
		{
			cout << endl << "卡余额为0，不能上机！ " << endl;
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else
	{
		cout << endl << endl << "卡号或者密码格式不正确，上机失败!" << endl <<
			endl;
	}
	delete pInfo;
}

void xiaJi(CardNode* pCardNodeHead, BillingNode* pBillingNodeHead)
{
	string strNo;
	string strPwd;
	SettleInfo* pInfo = new SettleInfo; // 下机信息
	char aStartTime[TIMELENGTH] = { 0 }; // 上机时间
	char aEndTime[TIMELENGTH] = { 0 }; // 下机时间
	if (inputNoPwd(strNo, strPwd))//输入账号，密码
	{
		cout << "----------下机信息如下----------\n";
		int nResult = settle(strNo, strPwd, pInfo, pCardNodeHead,pBillingNodeHead);
		switch (nResult)
		{
		case NOFINDCARD:
		case NOMATCH:
		{
			cout << endl << endl << "卡不存在，或卡信息不对，下机失败！ " <<
				endl << endl;
			break;
		}
		case SUCCESS:
		{
			timeToString(pInfo->tStart, aStartTime);
			timeToString(pInfo->tEnd, aEndTime);
			cout << endl;
			cout << "卡号: \t" << strNo << endl;
			cout << "消费: \t" << pInfo->fAmount << endl;
			cout << "余额: \t" << pInfo->fBalance << endl;
			cout << "上机时间： \t" << aStartTime << endl;
			cout << "下机时间： \t" << aEndTime << endl;
			break;
		}
		case UNUSE:
		{
			cout << endl << endl << "该卡没有上机！ " << endl << endl;
			break;
		}
		case ENOUGHMONEY:
		{
			cout << endl << endl << "卡余额不足，请先充值再下机！ " << endl
				<< endl;
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else
	{
		cout << endl << endl << "卡号或者密码格式不正确，下机失败!" << endl <<
			endl;
	}
	delete pInfo;
}

bool updateBilling(const Billing* pCard, const string pPath, int nCardIndex)
{
	fstream ofile;
	ofile.open(pPath, ios_base::in | ios_base::out);
	ofile.seekp(sizeof(Card)*nCardIndex, ios_base::beg);
	ofile.write((char*)pCard, sizeof(Card));
	ofile.close();
	return true;
}

int settle(string strNo, string strPwd, SettleInfo* pInfo, CardNode* const pCardNodeHead, BillingNode* const pBillingNodeHead)
{
	int nCardIndex;
	Card* pCard = cardIsExist(strNo, nCardIndex, pCardNodeHead);//查找与账号相同的卡
	// 未找到卡
	if (pCard == NULL)
		return NOFINDCARD;
	// 密码不匹配
	if (strcmp(pCard->aPwd, strPwd.c_str()) != 0)
		return NOMATCH;
	// 判断该卡是否正在上机，只有正在上机卡才能进行下机操作
	if (pCard->nStatus != USING)
		return UNUSE;
	// 根据卡号，查询计费信息
	int nBillingIndex;
	Billing* pBilling = billingIsExist(strNo, nBillingIndex, pBillingNodeHead);//nbillingindex用于定位
	// 如果查询计费信息为空，表示下机失败
	if (pBilling == NULL)
	{
		cout << "计费信息为空" << endl;
		return UNUSE;
	}
	// 计算消费金额
	double dbAmount = getAmount(pBilling->tStart);//计算上机子花的钱
	// 如果余额小于消费金额，则不能进行下机
	float fBalance = pCard->fBalance - (float)dbAmount;//更新余额
	if (fBalance < 0)
	{
		return ENOUGHMONEY;
	}
	// 更新卡信息
	pCard->fBalance = fBalance; // 余额
	pCard->nStatus = UNUSE; // 状态
	pCard->tLast = time(NULL); // 上次使用时间
	updateCard(pCard, CARDPATH, nCardIndex);// 更新计费信息
	pBilling->fAmount = (float)dbAmount; // 消费信息
	pBilling->nStatus = YESSETTLEMENT; // 状态，已结算
	pBilling->tEnd = time(NULL); // 下机时间								 
	// 更新文件中的计费信息
	updateBilling(pBilling, BILLINGPATH, nBillingIndex);
	// 组装下机信息
	strcpy(pInfo->aCardName, strNo.c_str()); // 卡号
	pInfo->fAmount = (float)dbAmount; // 消费金额
	pInfo->fBalance = fBalance; // 余额
	pInfo->tStart = pBilling->tStart; // 上机时间
	pInfo->tEnd = time(NULL); // 下机时间
	return SUCCESS;
}

double getAmount(time_t tStart)
{
	double dbAmount = 0; // 消费金额
	int nCount = 0; // 上机的时间单元数，每个单元15分钟
	int nSec = 0; // 消费时间(单位：秒)
	int nMinutes = 0; // 消费时间(单位：分钟)
	time_t tEnd = time(NULL); // 结算时间为当前时间
							  // 计算消费时长
	nSec = (int)(tEnd - tStart);
	nMinutes = nSec / 60;
	// 计算消费的时间单元数
	if (nMinutes % UNIT == 0)
	{
		nCount = nMinutes / UNIT;
	}
	else
	{
		nCount = nMinutes / UNIT + 1;
	}
	if (nCount == 0)
		nCount = 1;
	// 计算消费金额
	dbAmount = nCount * CHARGE;
	return dbAmount;
}

Billing* billingIsExist(string strNo, int& nBillingIndex, BillingNode *pBillingNodeHead)
{
	BillingNode *pBillingNode = pBillingNodeHead;
	nBillingIndex = 0;
	while (pBillingNode != NULL)
	{
		if (strcmp(pBillingNode->data.aCardName, strNo.c_str()) == 0 &&
			pBillingNode->data.nStatus == NOSETTLEMENT)
		{
			return &(pBillingNode->data);
		}
		pBillingNode = pBillingNode->next;
		nBillingIndex++;
	}
	return NULL;
}

int searchBilling( CardNode* pCardNodeHead, BillingNode* pBillingNodeHead) {


	string t0, t1;

	cout << endl << "请输入查询时间段(开始,如%d-%d-%d-%d:%d)：";
	cin >> t0;
	time_t tbegin = stringToTime(const_cast<char*>(t0.c_str()));//string为const char* 
	if (tbegin == -1) {
		cout << endl << "输入格式错误" << endl;
		return -1;
	}

	cout << endl << "请输入查询时间段(结束,如%d-%d-%d-%d:%d)：";
	cin >> t1;
	time_t tover = stringToTime(const_cast<char*>(t1.c_str()));
	if (tover == -1) {
		cout << endl << "输入格式错误" << endl;
		return -1;
	}

	BillingNode* pBillingNode = pBillingNodeHead;
	char aStartTime[TIMELENGTH] = { 0 };
	char aEndTime[TIMELENGTH] = { 0 };
	float sum = 0;

	cout << endl << endl << "卡号\t\t上机时间\t\t下机时间\t\t消费金额\t是否结算\n" << endl << endl;
	while (pBillingNode != NULL) {
		if (pBillingNode->data.tStart >= tbegin && pBillingNode->data.tEnd <= tover) {
			timeToString(pBillingNode->data.tStart, aStartTime);
			timeToString(pBillingNode->data.tEnd, aEndTime);
			cout << pBillingNode->data.aCardName << "\t";
			cout << aStartTime << "\t";
			if (pBillingNode->data.nStatus == 1) {
				cout << aEndTime << "\t";
			}
			else {
				cout << "该卡未下机" << "\t\t";
			}
			cout << pBillingNode->data.fAmount << "\t\t" << pBillingNode->data.nStatus << endl;
			sum += pBillingNode->data.fAmount;
		}
		pBillingNode = pBillingNode->next;
	}
	cout << endl << endl << "总消费金额为：" << sum << "元" << endl;
	return SUCCESS;
}


