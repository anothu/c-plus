#include<iostream>
using namespace std;
int main()
{
	int n;
	cin >> n;
	char *a = new char[n];
	int k;
	cin >> k;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}

	int m = n - k;


	char *b = new char[n];
	while (k > n)
	{
		k -= n;
	}

		for (int i = k; i < n; i++)
		{
			b[i - k] = a[i];
		}
		for (int j = 0; j < k; j++)
		{
			b[m] = a[j];
			m++;
		}
		
		for (int i = 0; i < n; i++)
		{
			cout << b[i];
	 }
		system("pause");
}
