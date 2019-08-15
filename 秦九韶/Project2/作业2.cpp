#include<iostream>
#include <stdlib.h>
using namespace std;
int main()
{
	int i;
	int n;
	int j;
	double x;
	double p = 0;
	double y = 1;
	cout << "请输入个数n：";
	cin >> n;
	cout << endl;
	cout << "请输入x：";
	cin >> x;
	double *a = new double[n];
	for (i = 0; i < n; i++)
	{
		cout << "请输入第" << i << "系数" << endl;
		cin >> a[i];
	}
	for (i = 0; i < n; i++)
	{
		p = (p*x) + a[i];
	}
	cout << "结果p是：" << p;
	cout << endl;
	system("pause");
	return 0;

}
