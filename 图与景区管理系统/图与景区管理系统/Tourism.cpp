
#include"stdafx.h"
#include<iostream>
#include <fstream>
#include"Tourism.h"
#include"Graph.h"
#include <string.h>
#include <vector>
#include <math.h>
#include<assert.h>
using namespace std;

extern CGraph m_Graph;

void CreatGraph()
{
	cout << "=====创建景点景区图=====" << endl;
	int n;
	FILE *in;
	in = fopen("VEX.TXT", "r");
	n = fgetc(in);

	Vex *sights=new Vex[999];
	for (int i = 0; i <n-48; i++)
	{
		fscanf(in, "%d %s %s ", &sights[i].num, sights[i].name, sights[i].desc);
	}
	fclose(in);

	FILE *road;
	road = fopen("EDGE.TXT", "r");
	
	Edge *Road=new Edge[999];
	int temp = 0;
	while (1)
	{
		fscanf(road, "%d %d %d", &Road[temp].vex1, &Road[temp].vex2, &Road[temp].weight);
		temp++;
		if (feof(road))
			break;
	}
	
	for (int i = 0; i < n-48; i++)
	{
		m_Graph.InsertVex(sights[i]);
	}
	for (int i = 0; i < temp; i++) 
	{
		m_Graph.InsertEdge(Road[i]);
	}
}
void GetSpotInfo()
{
	int nVexNum = m_Graph.m_nVexNum;
	if (nVexNum == 0) {
		cout << "请先创建图！" << endl;
		return;
	}
	cout << "请输入想要查找的景点编号: ";
	int section;
	cin >> section;
	Vex s=GetVex(section);
	cout << s.num << endl << s.name << endl << s.desc<<endl;
	cout << "----周边景区-------"<<endl;
	FindEdge(section);
}

void TravelPath()
{
	//先输出当前景点以及编号
	cout << "=====旅游景点导航=====" << endl;
	int nVexNum = m_Graph.m_nVexNum;
	if (nVexNum == 0) {
		cout << "请先创建图！" << endl;
		return;
	}
	for (int i = 0; i<m_Graph.m_nVexNum; i++)
	{
		Vex sVex = GetVex(i);
		cout << i << "-" << sVex.name << endl;
	}

	//提示用户选择景点起点
	cout << "请输入想要起始点编号：";
	int startplace;		//起点编号
	cin >> startplace;
	//判断用户输入是否符合规范
	if (startplace<0 || startplace >= m_Graph.m_nVexNum)
	{
		cout << "输入错误！" << endl;
		return;
	}

	//查询从startplace开始的路径信息
	PathList pList = new Path;
	PathList pHead = pList;
	//得到路径信息
	DFSTraverse(startplace, pList);

	//输出路径信息
	cout << "供参考路线：" << endl;
	int i = 1;
	pList = pHead;			//头指针一直在，将其赋值给pList，用来遍历链表
	while (pList->next != NULL)
	{
		//输出一条路径信息
		Vex sVex = GetVex(pList->vexs[0]);
		cout << "路线" << i++ << "：" << sVex.name;
		for (int j = 1; j<m_Graph.m_nVexNum; j++)
		{
			sVex = GetVex(pList->vexs[j]);
			cout << "->" << sVex.name;
		}
		cout << endl;
		pList = pList->next;		//指针继续下移，遍历下一个结点
	}
	cout << endl;
	//指针做处理
	delete pList;
	pList = NULL;
	pHead = NULL;
}

void ShortPath()
{
	int nVexNum = m_Graph.m_nVexNum;
	if (nVexNum == 0) {
		cout << "请先创建图！" << endl;
		return;
	}

	cout << "=========寻找最短路径==========" << endl;
	for (int i = 0; i<m_Graph.m_nVexNum; i++)
	{
		Vex sVex = GetVex(i);
		cout << i << "-" << sVex.name << endl;
	}
	cout << "输入出发点,目的地编号:"<<endl;
	int nVexStart, nVexEnd;
	cin >> nVexStart;
	cin >> nVexEnd;
	Edge path[999];
	FindShortPath( nVexStart,  nVexEnd,path);
	shortpath(path, nVexStart, nVexEnd);
}
void ElectricPath()
{
	int nVexNum = m_Graph.m_nVexNum;
	if (nVexNum == 0) {
		cout << "请先创建图！" << endl;
		return;
	}
	cout << "=========铺设电路规划==========" << endl;
	Edge path[999];
	int min = 99999999;
	int temp;
	for (int i = 0; i < m_Graph.m_nVexNum;i++)
	{
		if (findElectricpath(i, path) < min)
		{
			min = findElectricpath(i, path);
			temp = i;
		}
	}
	cout<<"总长度:"<<findElectricpath(temp, path)<<endl;
	cout << "铺设方式：";
	for (int i = 2; i <= m_Graph.m_nVexNum; i++)
	{
		cout << path[i].vex1 << "->" << path[i].vex2 << " ";
	}
}
