#include <iostream>
using namespace std;
int i, j, n, x1;
double p, sum;
double x[100];
double y[100];

int func(int m)
{
	sum = 0;
	p = 1;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < m; j++) {
			if (j != i) {
				p *= x[i] - x[j];
			}
		}
		sum += y[i] / p;
		p = 1;
	}
	return sum;
}
int main()
{
	cout << "要输入几组数据？";
	cin >> n;
	cout << "请输入数据：" << endl;
	for (i = 0; i < n; i++) {
		cin >> x[i];
		cin >> y[i];
	}
	cout << "求在x为何值的插值：" << endl;
	cin >> x1;
	int a = 0, b = 1;
	for (int u = 1; u <= n; u++)
	{
		for (int v = 0; v < u; v++)
		{
			if (v >= 1)
				b *= (x1 - x[v - 1]);
		}
		a += func(u)*b;
	}
	cout << "求得的f（x)的牛顿插值为：" << a << endl;
	return 0;
}