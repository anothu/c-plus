#include <iostream>
#include <cmath>
using namespace std;

long double x, e, a, b;
int k;

long double fx(long double x)
{
	return pow(x, 6) - x - 1;
}
int main()
{
	cout << "please input a,b£º" << endl;
	cin >> a >> b;
	cout << "please inout e£º" << endl;
	cin >> e;
	for (k = 1; fx(x) > e || fx(x) < -e; k++)
	{
		x = (a + b) / 2;
		if (fx(a)*fx(x) < 0)
		{
			b = x;
			cout << "x=" << x << "  " << "f(x)=" << fx(x) << endl;
		}
		else
		{
			a = x;
			cout << "x=" << x << "  " << "f(x)=" << fx(x) << endl;
		}
	}
	cout << k;
	system("pause");
}
