#include<iostream>
using namespace std;


int main()
{
	int i, j, k;
	int t;
	int n;
	int index;
	cin >> n;
	int a[99];

	for ( i = 0; i < n; i++)
	{
		cin >> t;
		a[i] = t;
	}
	int L[99];
	int x[99][99];
	for (i = 0; i < n; i++)
	{
		L[i] = 1;
		x[i][0] = a[i];
	}
	for (i = 1; i < n; i++)
	{
		int max = 1;
		for (j = i - 1; j >= 0; j--)
		{
			if ((a[i] <= a[j]) && (max < L[j] + 1))
			{
				max = L[j] + 1;
				L[i] = max;
				for (k = 0; k < max - 1; k++)
				{
					x[i][k] = x[j][k];
				}
				x[i][max - 1] = a[i];
			}
		}
	}
	for (index = 0, i = 1; i < n; i++)
	{
		if (L[index] < L[i])
			index = i;
	}
	cout << L[index];
}

