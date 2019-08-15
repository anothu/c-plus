// GraphCPro.cpp: 定义控制台应用程序的入口点。
#include"stdafx.h"
#include<iostream>
#include"Graph.h"
#include"Tourism.h"
using namespace std;

Graph m_Graph;


int main()
{
	while (1)
	{
		int choose;
		cout << "==========景区信息管理系统==========" << endl;
		cout << "1.创建景区景点图" << endl;
		cout << "2.查询景点信息" << endl;
		cout << "3.旅游景点导航" << endl;
		cout << "4.搜索最短路径" << endl;
		cout << "5.铺设电路规划" << endl;
		cout << "0.退出" << endl;
		cout << "请输入操作编号（0~5）:";
		cin >> choose;
		if ((choose != 1) && (choose != 2) && (choose != 3) && (choose != 4) && (choose != 5) && (choose != 0))
			cout << endl << "请输入正确的编号:";
		if (choose == 0)
		{
			cout << "==========已退出==========" << endl;
			break;
		}
		else
		{
			switch (choose)
			{
			case 1:
				CreateGraph();
				break;
			case 2:
				GetSPotInfo();
				break;
			case 3:
				TravelPath();
				break;
			case 4:
				FindShortPath();
				break;
			case 5:
				DesigePath();
				break;
			}
		}
	}

	return 0;
}

