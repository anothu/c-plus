#pragma once
#include"GameLogic.h"
#include"global.h"

class CGameControl
{
public:
	CGameControl();
	~CGameControl();
	void StartGame();
	int GetElement(int nRow, int nCol);
	void SetFirstPoint(int nRow, int nCol);             //设置第一个点函数
	void SetSecPoint(int nRow, int nCol);   //设置第二个点函数
	bool Link(Vertex avPath[4], int &nVexnum);
	Vertex m_svSelFst;	//第一次选中的点(x表示列)
	Vertex m_svSelSec;		//第二次选中的点
	
public:
	//int **m_PGameMap;
	static int s_nRows;
	static int s_nCols;
	static int s_nPicNum;
	int m_PGameMap[4][4];


};

