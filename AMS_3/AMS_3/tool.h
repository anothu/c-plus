#pragma once
#include<time.h>
#include<stdio.h>

void timeToString(time_t t, char* pBuf);
time_t stringToTime(char* pTime);