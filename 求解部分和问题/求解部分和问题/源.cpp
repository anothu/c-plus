#include<iostream>
using namespace std;
int main()
{
	int N, K;
	int s=0;
	int e = 0;
	int sum=0;
	cin >> N;
	cin >> K;
	int A[99];
	for (int i = 0; i < N; i++)
	{
		cin >> A[i];
	}
	while (s < N)
	{
		e = s;
		sum = A[s];
		if (sum == K)
		{
			cout << "YES";
			return 0;
		}
		if (sum > K)
		{
			s++;
			break;
		}
		else
		{
			e++;
		}
		while (e < N)
		{
			sum += A[e];
			if (sum  == K)
			{
				cout << "YES";
				return 0;
			}
			if (sum > K)
			{
				sum -= A[e];
				e++;
			}
			else
				e++;
		}
		s++;
	}
	cout << "NO";
	return 0;
}