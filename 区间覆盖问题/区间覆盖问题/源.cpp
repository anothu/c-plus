#include<iostream>
using namespace std;
int main()
{
	int n;
	cin >> n;
	int k;
	cin >> k;
	int a[99];
	int l=0;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (a[j] < a[i]) 
			{
				int temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
	int count = 0;
	if (a[0] + k >= a[n - 1])
		cout << count+1;
	else 
	{		
			for (int i = 0; i < n;i++)
			{
				int x = a[l] + k;
				if (x == a[i])
				{
					l = i + 1;
					count++;

				}
				else if (x > a[i] && x < a[i + 1])
				{
					l = i + 1;
					count++;
				}
				
			}
		cout << count+1;
		}	
	system("pause");
}