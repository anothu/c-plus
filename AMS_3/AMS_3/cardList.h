#include"menu.h"
#include"model.h"
#include <string.h> 
int addNewCard(string strNo, string strPwd, float fBalance, CardNode** ppCardNodeHead, MoneyNode** ppMoneyNodeHead);
CardNode* CardListInit(const string filename);
Card* cardIsExist(string strNo, int &nCardIndex, CardNode* pCardNodeHead);
void displayCard(CardNode* pCardNodeHead);
bool saveCard(const Card* pcard, const string pPath);