#include<iostream>
using namespace std;

int main()
{
	int n;
	int m = 0;
	cin >> n;
	int*a = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (a[i] > a[j])
				m++;
		}
	}
	cout << m;
}