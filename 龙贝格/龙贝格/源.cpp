/*#include <iostream>
#include<math.h>
using namespace std;

double a, b, e;
int k;
double T1, x, S, T2, S1, S2, C2, C1, R2, R1,h;
double f(double x)
{
	if (x == 1)
		return 1;
	else
		return sin(x)/x;
}
int main()
{
	cout << "please input a,b,e: ";
	cin >> a;
	cin >> b;
	cin >> e;
	h = b - a;
	T1 = (h / 2)*(f(a) + f(b));
	k = 1;
	do {
		do {
			do {
				do
				{
					S = 0;
					x = a + h / 2;
					do {
						S = S + f(x);
						x = x + h;
					} while (x < b);
					T2 = (h / 2)*S + T1/2;

					S2 = T2 + (T2 - T1) / 3; 
				} while (k == 1, k++, h = h / 2, T1 = T2, S1 = S2);
				C2 = S2 + (S2 - S1) / 15;
			} while (k == 2, C1 = C2, k++, h = h / 2, T1 = T2, S1 = S2);
		} while (k == 3, R1 = R2, C1 = C2, k++, h = h / 2, T1 = T2, S1 = S2);
	} while ((R2 - R1)<e&&(R2 - R1)>e);
	cout << R2;
	system("pause");
}*/

#include<iostream>
#include<math.h>
using namespace std;
int rk = 0;
double f(double x) {
	if (x == 0)
		return 1;
	return sin(x) / x;
}
double Tn(double a, double b, int k) { //n为2的k次幂
	int n = 1;
	double h = b - a;
	double t1, t2, s = 0, x;
	t1 = h / 2.0*(f(a) + f(b));
	if (k == 1)
		return t1;
	while (n<k) {
		s = 0; x = a + h / 2.0;
		while (x<b)
		{
			s = s + f(x); x += h;
		}
		t2 = t1 / 2.0 + h / 2.0*s;
		h /= 2.0;
		t1 = t2;
		n++;
	}
	return t2;
}
double longbeige(double a, double b, double e) {
	double t1, t2 = 0, s1, s2 = 0, c1, c2 = 0, r1, r2 = 0, s, x;
	double h = b - a;
	t1 = h / 2 * (f(a) + f(b));
	int k = 1;//计数
	while (k<20) {
		s = 0;
		x = a + h / 2.0;
		while (x<b)
		{
			s += f(x); x += h;
		}
		t2 = t1 / 2 + h*s / 2.0;
		cout << "T" << k << "：" << t2 << endl;
		s2 = t2 + 1 / 3.0*(t2 - t1);
		cout << "S" << k - 1 << "：" << s2 << endl;
		if (k == 1)
		{
			k++; h /= 2.0; t1 = t2; s1 = s2; continue;
		}
		c2 = s2 + 1 / 15.0*(s2 - s1);
		cout << "C" << k - 1 << "：" << c2 << endl;
		if (k == 2)
		{
			k++; h /= 2.0; t1 = t2; s1 = s2; c1 = c2; continue;
		}
		r2 = c2 + 1 / 63.0*(c2 - c1);
		if (k == 3)
		{
			k++; h /= 2.0; t1 = t2; s1 = s2; c1 = c2; r1 = r2; continue;
		}
		if (fabs(r1 - r2) >= e)
		{
			k++; continue;
		}
		else
		{
			cout << "R" << k - 4 << "：" << r2 << endl; break;
		}
	}
	return 0;
}

int main()
{
	double a, b;
	cout << "请输入a：";
	cin >> a;
	cout << "请输入b：";
	cin >> b;
	longbeige(a, b, 0.000001);
	system("pause");
}

