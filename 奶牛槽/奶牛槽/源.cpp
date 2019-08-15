#include<iostream>
using namespace std;

int setting(int t[99][2], int s[], int n)
{
	int m = 0;//畜栏个数
	s[0] = 1;
	m++;
	for (int i = 1; i<n; i++)
	{
		int h[99] = { 0 };
		for (int k = 0; k<i; k++)
		{
			if (t[k][0] <= t[i][1] && t[k][1] >= t[i][0])
				h[k] = 1;//如果出现重合，则置1 
		}
		for (int k = 0; k <= i; k++)
		{
			if (k == i)
			{
				s[i] = ++m;
			}
			else
			{
				if (h[k] == 0)
				{
					s[i] = s[k];
					break;
				}
			}
		}
	}
	return m;
}

int main()
{
	int t[99][2];
	int n;
	cin >> n;
	for (int i = 0; i<n; i++)
	{
		cin >> t[i][0];
		cin >> t[i][1];
	}
	int s[99] = { 0 };
	cout << setting(t, s, n)<<endl;
	for (int i = 0; i<n; i++)
	{
		cout << s[i] << endl;
	}
	system("pause");
}