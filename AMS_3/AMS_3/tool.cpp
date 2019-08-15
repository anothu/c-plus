#include"stdafx.h"
#include <time.h> // 包含时间类型头文件
#include <stdio.h> // 包含sscanf()函数头文件


void timeToString(time_t t, char* pBuf)
{
	struct tm * timeinfo;//定义时间变量指针
	timeinfo = localtime(&t);//获得tm结构体的时间
	strftime(pBuf, 20, "%Y-%m-%d %H:%M", timeinfo);//将时间格式化
}

time_t stringToTime(char* pTime)
{
	struct tm tm1;
	time_t time1;
	sscanf(pTime, "%d-%d-%d-%d:%d", &tm1.tm_year, &tm1.tm_mon,
		&tm1.tm_mday, &tm1.tm_hour, &tm1.tm_min);
	tm1.tm_year -= 1900; // 年份为从1900年开始
	tm1.tm_mon -= 1; // 月份为0~11
	tm1.tm_sec = 0;
	tm1.tm_isdst = -1;
	time1 = mktime(&tm1);
	return time1;
}//将标准化时间改为tm