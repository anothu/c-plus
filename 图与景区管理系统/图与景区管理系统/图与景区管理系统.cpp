// 图与景区管理系统.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iomanip>
#include<iostream>
#include"Graph.h"
#include"Tourism.h"
using namespace std;

CGraph m_Graph;

void information()
{	
	cout <<"顶点数 "<< m_Graph.m_nVexNum<<endl;

	//juzheng
	for (int i = 0; i < m_Graph.m_nVexNum; i++)
	{
		for (int j = 0; j < m_Graph.m_nVexNum; j++)
		{
			cout << left<<setw(4)<<m_Graph.m_aAdjMatrix[i][j] << "    ";
		}
		cout << endl;
	}
}

int main()
{
    cout << "=========景区信息管理系统=========="<<endl;
	cout << "1.创建景区景点图" << endl;
	cout << "2.查询景点信息" << endl;
	cout << "3.旅游景点导航" << endl;
	cout << "4.搜索最短路径" << endl;
	cout << "5.铺设电路规划" << endl;
	cout << "0.退出" << endl;
   
	//information();
	int choose;

	do {
		cout << "☆请选择功能：";
		cin >> choose;
		switch (choose)
		{
		case 1:
			CreatGraph();
			cout << "创建成功！"<<endl;
			cout << "==================="<<endl;
			continue;
		case 2:
			GetSpotInfo();

			cout <<endl<< "===================" << endl;
			continue;
		case 3:
			TravelPath();

			cout << endl << "===================" << endl;
			continue;
		case 4:
            ShortPath();

			cout << endl << "===================" << endl;
			continue;
		case 5:
			ElectricPath();

			cout << endl << "===================" << endl;
			continue;
		case 0:
			cout << "感谢使用本系统！";
		}
	}while(choose != 0);
	system("pause");


}

