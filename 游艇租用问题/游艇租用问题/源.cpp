#include<iostream>
#include<fstream>
#include<string>
using namespace std;


int dp[99][99];

int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

int main()
{

	ifstream myfile("F:\ship_in.txt");
	ofstream outfile("F:\ship_out.txt");
	int n;
	myfile >> n;
	for (int i = 1; i < n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			myfile >> dp[i][j];
		}
	}
	//动态规划
	for (int k = 2; k<n; k++)//记录旅途长度
	{
		for (int i = 1; i <= n - k; i++)//记录出发点
		{
			int j = i + k;
			for (int z = i + 1; z <= j; z++)//记录中转站
			{				 
				dp[i][j] = min(dp[i][j], dp[i][z] + dp[z][j]);
			}
		}
	}
	cout << dp[1][n];
	outfile << dp[1][n];
}
//min=dp[i][j]
//min=min(dp[i][j],dp[i][z]+dp[z][j])