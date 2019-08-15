#include<iostream>
using namespace std;
int main() {
	double a[100][100], result[100];
	int n, i, j, k, mid;
	cout << "请输入方程个数:" << endl;
	cin >> n;
	for (i = 0; i < n; i++) {
		cout << "请输入第" << i + 1 << "个方程的系数:" << endl;
		for (j = 0; j < n; j++) {
			cin >> a[i][j];
		}
	}

	for (i = 0; i < n; i++) {
		cout << "请输入第" << i + 1 << "个等式右边的数:";
		cin >> a[i][n];
	}
	for (i = 0; i<n; i++)
	{
		a[i][n] /= a[i][i];
		for (j = n - 1; j >= i; j--)
		{
			a[i][j] /= a[i][i];
		}
		for (j = i + 1; j<n; j++)
		{
			for (k = i + 1; k <= n; k++)
			{
				a[j][k] -= a[j][i] * a[i][k];
			}
			a[j][i] = 0;
		}
	}
	for (i = n - 1; i >= 0; i--)
	{
		if (i == n - 1)
		{
			result[i] = a[i][n];
		}
		else
		{
			for (j = n - 1; j > i; j--) {
				a[i][n] -= a[i][j] * a[j][n];
				a[i][j] = 0;
			}
			result[i] = a[i][n];
		}
	}
	for (i = 1; i <= n; i++)
		cout << "x" << i << "的值为:" << result[i - 1] << endl;
	system("pause");
}