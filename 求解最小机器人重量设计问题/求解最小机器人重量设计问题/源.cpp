#include<iostream>
#define MAXSIZE 150
using namespace std;
int main()
{
	int n, m, d;
	int d_now = 0;//当前总价值 
	int w_now = 0;//当前重量 
	int w_min = 100;//最小重量 
	cin >> n;
	cin >> m;
	cin >> d;
	int w[MAXSIZE][MAXSIZE];
	int c[MAXSIZE][MAXSIZE];
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			cin >> w[i][j];
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			cin >> c[i][j];
		}
	}
	int p[MAXSIZE];//存储各部件对应供应商编号
	int pmin[MAXSIZE];//存储最小重量对应供应商编号 
	for (int i = 1; i <= n; i++)
		p[i] = 0;
	int t = 1;//行 
	int q = 1;//列 
	while (t>0)
	{
		

		if (d_now + c[t][q]>d)
		{
			if (q<m)                //下一个供应商 
				q++;
			else                //上一个部件 
			{
				t--;
				d_now -= c[t][p[t]];
				w_now -= w[t][p[t]];
				while (p[t] >= m)
				{
					t--;
					d_now -= c[t][p[t]];
					w_now -= w[t][p[t]];
					if (t <= 0)
						break;
				}
				q = p[t] + 1;
			}
		}
		else
		{
			d_now += c[t][q];
			w_now += w[t][q];
			
			p[t] = q;
			if (t == n)//已到最后一个部件 
			{
				if (w_now<w_min)
				{
					for (int i = 1; i <= n; i++)
						pmin[i] = p[i];
					w_min = w_now;
					
				}
				if (q<m)
				{
					w_now -= w[t][q];
					d_now -= c[t][q];
					q++;
				}
				else
				{

					d_now -= c[t][p[t]];
					w_now -= w[t][p[t]];
					t--;
					
					d_now -= c[t][p[t]];
					w_now -= w[t][p[t]];
					
					while (p[t] >= m)
					{
						
						d_now -= c[t][p[t]];
						w_now -= w[t][p[t]];
						t--;
						if (t <= 0)
							break;
					}
					q = p[t] + 1;
				}
			}
			else//未到最后一个部件 
			{
				t++;
				q = 1;
			}
		}

	}
	for (int i = 1; i<n; i++)
	{
		cout<< pmin[i]<<" ";
	}
	cout << pmin[n];
	cout << endl;
	cout<<w_min;
	system("pause");
	return 0;
}
/*int main()
{
int n, m, d;
cin >> n;
cin >> m;
cin >> d;
int w[99][99];
int c[99][99];
int weight = 0;
int cost = 0;
int wmin = 100;
for (int i = 1; i <= n; i++)
{
for (int j = 1; j <= m; j++)
{
cin >> w[i][j];
}
}
for (int i = 1; i <= n; i++)
{
for (int j = 1; j <= m; j++)
{
cin >> c[i][j];
}
}
int hang = 1;
int lie = 1;
int p[99];
for (int i = 1; i <= n; i++)
{
p[i] = 0;
}
int pmin[99];
while (hang > 0)
{
if (cost + c[hang][lie] > d)
{
if (lie < m)
lie++;
else
{
hang--;
cost -= c[hang][p[hang]];
weight -= w[hang][p[hang]];
while (p[hang] >= m)
{
hang--;
cost -= c[hang][p[hang]];
weight -= w[hang][p[hang]];
if (hang <= 0)
break;
}
lie = p[hang] + 1;
}
}
else
{
cost += c[hang][lie];
weight += w[hang][lie];
p[hang] = lie;

if (hang == n)
{
if (weight < wmin)
{
for (int i = 1; i <= n; i++)
{
pmin[i] = p[i];
}
wmin = weight;
}


if (lie < m)
{
weight -= w[hang][lie];
cost -= c[hang][lie];
lie++;
}
else
{
cost -= c[hang][p[hang]];
weight -= w[hang][p[hang]];
hang--;
cost -= c[hang][p[hang]];
weight -= w[hang][p[hang]];
while (p[hang] >= m)
{
hang--;
cost -= c[hang][p[hang]];
weight -= w[hang][p[hang]];

if (hang <= 0)
{
break;
}
}
lie = p[hang] + 1;
}
}
else {
hang++;
lie = 1;
}
}

}
for (int i = 1; i < n; i++)
{
cout << pmin[i];
}
cout << wmin;
system("pause");
}*/