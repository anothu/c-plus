#include<iostream>
#include<fstream>
#include<string>
using namespace std;


int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

int medium(int n,int* a,int* b)
{
	int  c1,c2, r1, r2, l1, l2;
	int d = n;	
	while (1)
	{	
		 c1 = d;
		 c2 = 2 * n - c1;
		 l1 = (c1 - 1) / 2;
		 l2 = (c2 - 1) / 2;
		 r1 = c1 / 2;
		 r2 = c2 / 2;
		if (c1 == -1)
			return b[n / 2] + b[(n - 1) / 2];
		else if (c1 == 2 * n)
			return a[n / 2] + a[(n - 1) / 2];
		else if (a[l1] > b[r2])
			d -= 1;
		else if (b[l2] > a[r1])
			d += 1;
		else
			break;
	}
	return ((max(a[l1], b[l2])) + min(b[r1], b[r2])) / 2.0;

}

int main()
{
	ifstream myfile("F:\demo\\test.txt" );
	ofstream outfile("F:\demo\\output.txt");
	int n, *x, *y;
	int result;
	myfile >> n;
	x = new int[n];
	y = new int[n];
	for (int i = 0; i < n; i++)
	{
		myfile >> x[i];
	
	}

	for (int j = 0; j < n; j++)
	{
		myfile >> y[j];
		
	}
	int t;
	t = medium(n, x, y);
    outfile << t;
	cout << t;
	system("pause");
}