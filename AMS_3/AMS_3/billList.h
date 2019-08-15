

#include"model.h"
#include <string> 
#include "global.h"


BillingNode* BillListInit(const string billingFilename);
int logon(string strNo, string strPwd, LogonInfo* pInfo, CardNode* pCardNodeHead,BillingNode **ppBillingNodeHead);
bool saveBilling(const Billing* pBill, const string pPath);
bool updateCard(const Card* pCard, const string pPath, int nCardIndex);
void shangji(CardNode* pCardNodeHead, BillingNode **ppBillingNodeHead);
void xiaJi(CardNode* pCardNodeHead, BillingNode* pBillingNodeHead);
int settle(string strNo, string strPwd, SettleInfo* pInfo, CardNode* const pCardNodeHead, BillingNode* const pBillingNodeHead);
double getAmount(time_t tStart);
Billing* billingIsExist(string strNo, int& nBillingIndex, BillingNode *pBillingNodeHead);
bool updateBilling(const Billing* pCard, const string pPath, int nCardIndex);
int searchBilling(CardNode* pCardNodeHead, BillingNode* pBillingNodeHead);
