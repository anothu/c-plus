#pragma once

struct Vex
{
	int num;//编号
	char name[20];//名称
	char desc[1024];//介绍
};

struct Edge
{
	int vex1;//第一个顶点
	int vex2;//第二个顶点
	int weight;//权值
};

class CGraph
{
public:
	bool InsertVex(Vex sVex);
	bool InsertEdge(Edge sEdge);
	int m_aAdjMatrix[20][20];//邻接矩阵
	Vex m_aVexs[20];//顶点信息数组
	int m_nVexNum;//当前图的顶点个数
};

void Init();
Vex GetVex(int v);
int FindEdge(int a);

typedef struct Path
{
	int vexs[20];
	Path *next;
}*PathList;

void DFS(int v, bool bVisited[], int &index, PathList &plist);
void DFSTraverse(int nVex, PathList & pList);
int FindShortPath(int nVexStart, int nVexEnd,Edge* path);
void shortpath(Edge path[], int nVexStart, int nVexEnd);
int findpathweight(Edge*path, int j, int n);
int i_s(int*a, int i, int num);
int findElectricpath(int nVexStart, Edge*path);
//void Minelectric();