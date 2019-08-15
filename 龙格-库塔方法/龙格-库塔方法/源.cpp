#include<iostream>
using namespace std;


double f(double x, double y)
{
	return y - (2 * x / y);
}

int main()
{
	double h, N;
	double k1, k2, k3, k4;
	double x0, y[99];
	cout << "请输入x0 ";
	cin >> x0;
	cout << "请输入步长h ";
	cin >> h;
	cout << "请输入y[0] ";
	cin >> y[0];
	cout << "请输入N ";
	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		double xn = x0 + (i-1)*h;
		k1 = f(xn, y[i - 1]);
		k2 = f(xn + h / 2, y[i - 1] + h*k1 / 2);
		k3 = f(xn + h / 2, y[i - 1] + h*k2 / 2);
		k4 = f(xn + h, y[i - 1] + h*k3);
		y[i] = y[i - 1] + h*(k1 + 2*k2 + 2*k3 + k4) / 6;
		cout << "y["<<i<<"] :" << y[i]<<endl;
	}
	system("pause");
}