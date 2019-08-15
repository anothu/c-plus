#include<iostream>
using namespace std;

int main()
{
	int n;
	int c;
	cin >> n;
	int *a = new int[n];
	for(int i=0;i<n;i++)
	{
		cin >> a[i];
	}

	int min=a[1]-a[0];
	if (min < 0)
	{
		min = -min;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = i+1; j < n;j++)
		{
			if (a[i] > a[j])
			{
				c = a[i] - a[j];
			}
			else
			{
				c = a[j] - a[i];
			}
			if (c < min)
				min = c;
		}
	}
	cout << min;
	system("pause");
}
