#include<iostream>
using namespace std;

double sum(int n, double x[])
{
	double t=0;
	for (int i = 0; i < n; i++)
	{
		t = t + x[i];
	}
	return t;
}
int main()
{
	double x[99];
	double y[99];
	double z[99];
	double xx[99];
	int n;
	cout << "please input n:";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "No." << i << ": ";
		cin >> x[i];
		cin >> y[i];
		z[i] = x[i] * y[i];
		xx[i] = x[i] * x[i];
	}
	double b, a;
	b = (n*sum(n, z)-sum(n,x)*sum(n,y))/(n*sum(n,xx)-sum(n,x)*sum(n,x));
	a = (sum(n,y)/n)-(b*(sum(n,x)/n));
	cout << "线性拟合方程是y=" << a << "+" << b << "x";
	system("pause");
}