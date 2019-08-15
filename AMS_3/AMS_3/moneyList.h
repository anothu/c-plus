#include"model.h"
#include <string> 
#include "global.h"
MoneyNode* MoneyListInit(const string billingFilename);

bool saveMoney(const Money* pBill, const string pPath);

int recharge(string strNo, string strPwd, float fMoney, MoneyInfo* pInfo, CardNode* pCardNodeHead, MoneyNode** ppMoneyNodeHead);

int returnMoney(string strNo, string strPwd, MoneyInfo* pInfo, CardNode* pCardNodeHead, MoneyNode** ppMoneyNodeHead);

void addMoney(CardNode* pCardNodeHead, MoneyNode** ppMoneyNodeHead);

void refundMoney(CardNode* pCardNodeHead, MoneyNode** ppMoneyNodeHead);

int annulCard(string strNo, string strPwd, MoneyInfo* pInfo, CardNode* pCardNodeHead, MoneyNode** ppMoneyNodeHead);