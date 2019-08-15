#include"stdafx.h"
#include <iostream>

using namespace std;

bool funca(long a)
{
	int x, y;
	x = 0;
	y = 0;
	long t1, t2;
	t1 = a;
	while (t1 > 0)
	{
		y += t1 % 10;
		t1 /= 10;
	}                          //求各个位数字和
	t2 = a;
	int n = 0; //初始化
	while (t2 > 1)
	{
		for (int i = 2; i <= t2; i++)
		{
			if (t2%i == 0) //短除法
			{
				t2 = t2 / i;
				n++;
				break;
			}
		}
	}
	int *b = new int[n];
	n = 0;
	while (a > 1)
	{

		for (int i = 2; i <= a; i++)
		{
			if (a%i == 0)
			{
				a = a / i;
				b[n] = i;
				n++;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (b[i] > 9) {
			while (b[i] > 0)
			{
				x += b[i] % 10;
				b[i] /= 10;
			}
		}
		else x += b[i];
	}
	if (x == y)return true;
	else return false;
}
bool funcb(long a)
{
	int n = 0;
	for (int i = 2; i <a - 1; i++) {
		if (a%i == 0) {
			n++;
		}
	}
	if (n == 0)return true;
	else return false;
}
int funcc(long a)
{
	if (funcb(a)) {
		a++;
		funcc(a);
	}
	else if (funca(a))return a;
	else {
		a++;
		funcc(a);
	}
}
int main()
{
	long a;
	int n = 20;
	int *m = new int[n];
	n = 0;
	while (1)
	{
		cin >> a;
		if (a == 0)break;
		else {
			m[n] = funcc(a);
			n++;
		}
	}
	for (int i = 0; i < n; i++)
	{
		cout << m[i] << endl;
	}
	delete[]m;
	return 0;
}
