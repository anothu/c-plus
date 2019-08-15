#include <iostream>
#include <cmath>
using namespace std;

long double x, x1, e;
int n;
long double fx(long double x)
{
	return x*x - 115;
}
long double f1x(long double x)
{
	return 2 * x;
}
void main()
{
	cout << "please input x,e,n" << endl;
	cin >> x;
	cin >> e;
	cin >> n;
	for (int k = 1; k <= n; k++, x = x1)
	{
		if (f1x(x) == 0)
		{
			cout << "ÆæÒì" << endl;
			break;
		}

		x1 = x - fx(x) / f1x(x);
		cout << x1 << endl;
		if (-e < x1 - x && x1 - x < e)
		{
			cout << x1 << endl;
			break;
		}
	}
	system("pause");
}