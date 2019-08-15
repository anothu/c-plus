
#include"stdafx.h"
#include<iostream>
#include"Graph.h"
#define MAX_VERTEX_NUM  20
using namespace std;

extern CGraph m_Graph;

void Init()
{
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			m_Graph.m_aAdjMatrix[i][j] = 0;	
		}
		m_Graph.m_nVexNum = 0;				
	}
	
}
bool CGraph::InsertVex(Vex sVex)
{
	if (m_nVexNum == MAX_VERTEX_NUM)
	{
		//顶点已满
		return 0;
	}
	m_aVexs[m_nVexNum] = sVex;//插入顶点信息
	m_nVexNum++;
	return 1;
}

bool CGraph::InsertEdge(Edge sEdge)
{
	if (sEdge.vex1 < 0 || sEdge.vex1 >= m_nVexNum || sEdge.vex2 < 0 || sEdge.vex2 >= m_nVexNum)
	{
		//下标越界
		return 0;
	}
	//插入边的信息
	m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
	return 1;
}

Vex GetVex(int v)
{
	return m_Graph.m_aVexs[v];
}


int FindEdge(int a)
{
	int k = 0;
	for (int i = 0; i < m_Graph.m_nVexNum; i++)
	{
		
			if (m_Graph.m_aAdjMatrix[a][i] != 0)
			{
				cout << GetVex(a).name << "-->" << GetVex(i).name<<" "<< m_Graph.m_aAdjMatrix[a][i] << "m"<<endl;
				k++;
			}
		
	}
	return k;
}


void DFS(int v, bool bVisited[], int &index, PathList &plist)
{
	bVisited[v] = true;//该点状态改为被访问过
	plist->vexs[index]=v;
	index++;
	int v_num = 0;
	for (int i = 0; i<m_Graph.m_nVexNum; i++)
	{
		if (bVisited[i])
			v_num++;
	}

	if (v_num == m_Graph.m_nVexNum)
	{
		//创建一个新链表，将当前的pList中的数据保存起来
		plist->next = new Path;
		for (int i = 0; i<m_Graph.m_nVexNum; i++)
		{
			plist->next->vexs[i] = plist->vexs[i];
		}
		plist = plist->next;		//pList指针继续往下移动，寻找下一条路径
		plist->next = NULL;			//next赋值为空
	}
	else 
	{
		for (int i = 0; i < m_Graph.m_nVexNum; i++)
		{
			if (m_Graph.m_aAdjMatrix[v][i] > 0 && !bVisited[i])
			{
				DFS(i, bVisited, index, plist);
				bVisited[i] = false;						
				index--;
			}
		}
	}

}
void DFSTraverse(int nVex, PathList &pList)
{
	int nIndex = 0;					//遍历深度
	bool bVisited[20] = {false};  //所有的景点起始均为未访问
	DFS(nVex, bVisited, nIndex, pList);
}
int findpathweight(Edge*path,int endplace, int n)
{
	for (int i = 1; i <= n; i++)
	{
		if (path[i].vex2 == endplace)
		{

			return path[i].weight; 
		}
			
	}
	return 0;
}
int i_s(int*a,int i,int num)
{
	for (int j = 0; j < num;j++ )
	{
		if (i == a[j])
			return 1;
	}
	return 0;
}
int FindShortPath(int nVexEnd,int nVexStart,Edge*path)
{

	int s[20] = {0};
	s[0] = nVexStart;
	int NumOfs;//s中的元素个数
	NumOfs = 1;
	path[1].vex2 = nVexStart;
	path[1].weight = 0;
	while (1) 
	{
		
		int temp1;//起点
		int temp2;//终点
		int shortest = 99999;
		for (int i = 0; i < m_Graph.m_nVexNum; i++)
		{
			if(i_s(s,i,NumOfs))
			{
				continue;
			}
	//排除下一个点在s中
		
			for (int j = 0; j < NumOfs; j++)
			{
				int formerweight=findpathweight(path,s[j],NumOfs);
		
				if (m_Graph.m_aAdjMatrix[i][s[j]]+formerweight < shortest&&m_Graph.m_aAdjMatrix[s[j]][i] != 0)
				{
					shortest = m_Graph.m_aAdjMatrix[i][s[j]]+formerweight;
					temp1 = s[j];
					temp2 = i;
				}
			}	
		}	
		s[NumOfs] = temp2;
		NumOfs++;//s中元素增加
		path[NumOfs].vex1 = temp1;
		path[NumOfs].vex2 = temp2;
		path[NumOfs].weight = shortest;
		if (path[NumOfs].vex2 == nVexEnd)
		{
			cout <<"最短的路程长度为：" <<path[NumOfs].weight<<"m"<<endl;
			cout << "该路线为：";
		}
		if(NumOfs==m_Graph.m_nVexNum)
		{
			break;
		}
		
	}
	return 0;
}
void shortpath(Edge path[],int nVexEnd,int nVexStart)
{
	int temp=0;

	for (int i = 2; i <= m_Graph.m_nVexNum; i++)
	{
		if (path[i].vex2 == nVexEnd)
		{
			temp = i;
			cout << GetVex(path[i].vex2).name << "->" << GetVex(path[i].vex1).name<<" ";
			
		}	
	}

	if (path[temp].vex1 == nVexStart)
	{
		return;
	}

	shortpath(path, nVexStart, path[temp].vex1);
		
}


int findElectricpath(int nVexStart, Edge*path)
{
	int sum = 0;
	int s[20] = { 0 };
	s[0] = nVexStart;
	int NumOfs;//s中的元素个数
	NumOfs = 1;
	path[1].vex2 = nVexStart;
	path[1].weight = 0;
	while (1)
	{

		int temp1;//起点
		int temp2;//终点
		int shortest = 99999;
		for (int i = 0; i < m_Graph.m_nVexNum; i++)
		{
			if (i_s(s, i, NumOfs))
			{
				continue;
			}
			//排除下一个点在s中

			for (int j = 0; j < NumOfs; j++)
			{
				int formerweight = findpathweight(path, s[j], NumOfs);

				if (m_Graph.m_aAdjMatrix[i][s[j]] < shortest&&m_Graph.m_aAdjMatrix[s[j]][i] != 0)
				{
					shortest = m_Graph.m_aAdjMatrix[i][s[j]] ;
					temp1 = s[j];
					temp2 = i;
				}
			}
		}
		s[NumOfs] = temp2;
		NumOfs++;//s中元素增加
		path[NumOfs].vex1 = temp1;
		path[NumOfs].vex2 = temp2;
		path[NumOfs].weight = shortest;
		sum += shortest;
		//cout << path[NumOfs].vex1 << " " << path[NumOfs].vex2 << " " << path[NumOfs].weight << endl;
		if (NumOfs == m_Graph.m_nVexNum)
		{
			break;
		}

	}
	return sum;
}
/*void Minelectric()
{
	Edge path[999];
	int min=99999999;
	int temp;
	for (int i = 0; i < m_Graph.m_nVexNum; i++)
	{
		if (Electricpath(i, path) < min)
		{
			min = Electricpath(i, path);
			temp = i;
		}
	}
	Electricpath(temp, path);
	for (int i = 2; i <= m_Graph.m_nVexNum; i++)
	{
		cout << path[i].vex1 << "->" << path[i].vex2<<" ";
	}
	cout<<endl << "最小生成树大小为: " << min;
}*/