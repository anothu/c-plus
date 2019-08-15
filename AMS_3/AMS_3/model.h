#pragma once
#include<time.h>


struct Card
{
	 char aName[18]; // 卡号
	char aPwd[8]; // 密码
	int nStatus; // 卡状态(UNUSE-未上机； USING-正在上机； INVALID-已注销)
	 time_t tStart; // 开卡时间， long
	float fTotalUse; // 累计金额
	 time_t tLast; // 最后使用时间， long
	int nUseCount; // 使用次数
	float fBalance; // 余额

};

struct CardNode
{
	Card data;
	struct CardNode* next;
};


//计费信息结构体
struct Billing
{
	char aCardName[18];
	time_t tStart;
	time_t tEnd;
	float fAmount;
	int nStatus;
	int nDel;
};

//计费信息node
struct BillingNode
{
	Billing data;
	struct BillingNode *next;
};

//上机结构体
struct LogonInfo
{
	char aCardName[18];
	time_t tLogon;
	float fBalance;
};


//下机结构体
struct SettleInfo
{
	char aCardName[18];
	time_t tStart;
	time_t tEnd;
	float fAmount;
	float fBalance;
};

struct Money
{
	char aCardName[18]; // 卡号
	char aPwd[8]; // 密码
	int nStatus; // 卡状态(UNUSE-未上机； USING-正在上机； INVALID-已注销)
	time_t tTime; // 开卡时间， long
	float fBalance; // 余额
	float fMoney;//充上的钱
	int nDel;
};

struct MoneyNode
{
	Money data;
	struct MoneyNode *next;
};

struct MoneyInfo
{
	char aCardName[18]; // 卡号
	char aPwd[8]; // 密码
	int nStatus; // 卡状态(UNUSE-未上机； USING-正在上机； INVALID-已注销)
	time_t tTime; // 开卡时间， long
	float fMoney; // 累计金额
	time_t tLast; // 最后使用时间， long
	int nUseCount; // 使用次数
	float fBalance; // 余额
};