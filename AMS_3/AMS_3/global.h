#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#include <string>
using namespace std;
const string CARDPATH = "card.dat"; // 卡信息记录文件
const string BILLINGPATH = "billing.dat"; // 计费信息记录文件
const string MONEYPATH = "money.dat"; // 充值退费记录文件
const int TIMELENGTH = 20; // 时间字符数组长度
const int SUCCESS = 0; // 操作成功
const int FINDCARD = 1; // 找到卡
const int NOFINDCARD = 2; // 没找到卡
const int NOMATCH = 3; // 卡号密码不匹配
const int ENOUGHMONEY = 4; // 卡余额不足
const int NOFARE = 5; // 没有找到计费信息
const int USING = 6; // 卡状态：正在上机
const int UNUSE = 7; // 卡状态：没有上机
const int INVALID = 8; // 卡状态：已经注销
const int NOSETTLEMENT = 0; // 上机已结算
const int YESSETTLEMENT = 1; // 上机未结算
const int UNIT = 15; // 最小收费单元(分钟)
const float CHARGE = 0.5f; // 每个计费单元收费(元)
#endif // GLOBAL_H_INCLUDED