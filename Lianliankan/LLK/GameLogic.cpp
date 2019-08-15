#include "stdafx.h"
#include "GameLogic.h"
#include"GameControl.h"
#include"GameException.h"
#include<iostream>  
#include<stdlib.h>

CGameLogic::CGameLogic()
{
}


CGameLogic::~CGameLogic()
{
}

void CGameLogic::InitMap(int pGameMap[][4])
{
	int anTemp[4][4] = { 2,0,1,3,2,2,1,3,2,1,0,0,1,3,0,3 };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			pGameMap[i][j] = anTemp[i][j];
		}
	}

}
/*void CGameLogic::ReleaseMap(int **&pGameMap)
{
	for (int i = 0; i< CGameControl::s_nRows; i++)
	{
		delete[]pGameMap[i];
	}
	delete[]pGameMap;
}
int** CGameLogic::InitMap()
{
	int nrows = CGameControl::s_nRows;
	int ncols = CGameControl::s_nCols;
	int npicnum = CGameControl::s_nPicNum;

	int**pGameMap = new int *[nrows];
	if (NULL == pGameMap)
	{
		throw new CGameException(_T("内存操作异常！"));
	}
	else
	{
		for (int i = 0; i < nrows; i++)
		{
			pGameMap[i] = new int[ncols];
			if (NULL == pGameMap)
			{
				throw new CGameException(_T("内存操作异常！"));
			}
			memset(pGameMap[i], NULL, sizeof(int)*ncols);
		}
	}
	if ((nrows*ncols) % (npicnum * 2) != 0)
	{
		ReleaseMap(pGameMap);
		throw new CGameException(_T("游戏花色与游戏地图不匹配！"));
	}
	int nrepeatnum = nrows*ncols / npicnum;
	int ncount = 0;
	 for(int i = 0; i < npicnum; i++)
	{
		for (int j = 0; j < nrepeatnum; j++)
		{
			pGameMap[ncount / ncols][ncount % ncols] = i;
			ncount++;
		}
	}

	 //设置种子
	 srand((int)time(NULL));

	 int nvertexnum = nrows*ncols;
	 for (int i = 0; i < nvertexnum; i++)
	 {
		 int nindex1 = rand() % nvertexnum;
		 int nindex2 = rand() % nvertexnum;

		 int ntemp = pGameMap[nindex1 / ncols][nindex1 % ncols];
		 pGameMap[nindex1 / ncols][nindex1%ncols] = pGameMap[nindex2 / ncols][nindex2%ncols];
		 pGameMap[nindex2 / ncols][nindex2%ncols] = ntemp;
	 }
	 return pGameMap;
}*/


void CGameLogic::PopVertex()
{
	m_nVexNum--;
}

void CGameLogic::PushVertex(Vertex nV)
{
	m_avPath[m_nVexNum] = nV;
	m_nVexNum++;
}
bool CGameLogic::IsLink(int pGameMap[][4], Vertex v1, Vertex v2)
{
	int nCol1 = v1.col;
	int nRow1 = v1.row;
	int nCol2 = v2.col;
	int nRow2 = v2.row;
	PushVertex(v1);
	if (nRow1 == nRow2)
	{
		if (LinkInRow(pGameMap, v1, v2) == true)
		{
			PushVertex(v2);
			return true;
		}

	}
	if (nCol1 == nCol2)
	{
		if (LinkInCol(pGameMap, v1, v2) == true)
		{
			PushVertex(v2);
			return true;
		}
	}
	if (OneCornerLink(pGameMap, v1, v2) == true)
	{
		PushVertex(v2);
		return true;
	}
	if (TwoCornerLink(pGameMap, v1, v2) == true)
	{
		PushVertex(v2);
		return true;
	}
	return true;

}

bool CGameLogic::LinkInRow(int pGameMap[][4], Vertex v1, Vertex v2)
{
	int ncol1 = v1.col;
	int ncol2 = v2.col;
	int nRow = v1.row;
	if (ncol1 > ncol2)
	{
		int temp = ncol1;
		ncol1 = ncol2;
		ncol2 = temp;
	}
	for (int i = ncol1 + 1; i <= ncol2; i++)
	{
		if (i == ncol2)
		{
			return true;
		}
		if (pGameMap[nRow][i] != BLANK)
		{
			break;
		}
	}
	return false;
}
bool CGameLogic::LinkInCol(int pGameMap[][4], Vertex v1, Vertex v2)
{
	int nrow1 = v1.row;
	int nrow2 = v2.row;
	int ncol=v1.col;
	if (nrow1 > nrow2)
	{
		int temp = nrow1;
		nrow1 = nrow2;
		nrow2 = temp;
	}
	for (int i = nrow1 + 1; i <= nrow2; i++)
	{
		if (i == nrow2)
		{
			return true;
		}
		if (pGameMap[i][ncol] != BLANK)
		{
			break;
		}	
	}
	return false;
}
bool CGameLogic::LinkY(int pGameMap[][4], int nRow1, int nRow2, int nCol)
{
	for (int nRow = nRow1; nRow <= nRow2; nRow++)
	{
		if (nRow == nRow2)return true;
		if (pGameMap[nRow][nCol] != BLANK) break;
	}
	return false;
}
bool CGameLogic::LinkX(int pGameMap[][4], int nRow, int nCol1, int nCol2)
{
	for (int nCol = nCol1; nCol <= nCol2; nCol++)
	{
		if (nCol == nCol2)return true;
		if (pGameMap[nRow][nCol] != BLANK) break;
	}
	return false;
}

bool CGameLogic::OneCornerLink(int pGameMap[][4], Vertex v1, Vertex v2)
{
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	if (nRow1 > nRow2)
	{
		int nTemp = nRow1;
		nRow1 = nRow2;
		nRow2 = nTemp;
		int nTemp1 = nCol1;
		nCol1 = nCol2;
		nCol2 = nTemp1;
	}
	if (nCol2<nCol1)
	{
		if (pGameMap[nRow1][nCol2] == BLANK)
		{
			if (LinkX(pGameMap, nRow1, nCol2 + 1, nCol1) && LinkY(pGameMap, nRow1 + 1, nRow2, nCol2))
			{
				Vertex v = { nRow1, nCol2,BLANK };
				PushVertex(v);
				return true;
			}
		}
		if (pGameMap[nRow2][nCol1] == BLANK)
		{
			if (LinkY(pGameMap, nRow1 + 1, nRow2, nCol1) && LinkX(pGameMap, nRow2, nCol2 + 1, nCol1))
			{
				Vertex v = { nRow2, nCol1,BLANK };
				PushVertex(v);
				return true;
			}
		}
	}
	else
	{
		if (pGameMap[nRow1][nCol2] == BLANK)
		{
			if (LinkX(pGameMap, nRow1, nCol1 + 1, nCol2) && LinkY(pGameMap, nRow1 + 1, nRow2, nCol2))
			{
				Vertex v = { nRow1, nCol2,BLANK };
				PushVertex(v);
				return true;
			}
		}
		if (pGameMap[nRow2][nCol1] == BLANK)
		{
			if (LinkY(pGameMap, nRow1 + 1, nRow2, nCol1) && LinkX(pGameMap, nRow2, nCol1 + 1, nCol2))
			{
				Vertex v = { nRow2,nCol1,BLANK };
				PushVertex(v);
				return true;
			}
		}
	}
	return false;
}
bool CGameLogic::TwoCornerLink(int pGameMap[][4], Vertex v1, Vertex v2)
{

	int nCol1 = v1.col;
	int nCol2 = v2.col;
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	for (int nCol = nCol1; nCol < nCol2; nCol++)
	{
		if (pGameMap[nRow1][nCol] == BLANK && pGameMap[nRow2][nCol] == BLANK)
		{
			if (LinkY(pGameMap, nRow1, nRow2, nCol))
			{
				if (LinkX(pGameMap, nRow1, nCol1, nCol) && LinkX(pGameMap, nRow2, nCol2, nCol))
				{
					Vertex vx1 = { nRow1,nCol,BLANK };
					Vertex vx2 = { nRow2,nCol,BLANK };
					PushVertex(vx1);
					PushVertex(vx2);
					return true;
				}
			}
		}
	}
	for (int nRow = nRow1; nRow < nRow2; nRow++)
	{
		if (pGameMap[nRow][nCol1] == BLANK && pGameMap[nRow][nCol2] == BLANK)
		{
			if (LinkX(pGameMap, nRow, nCol1, nCol2))
			{
				if (LinkY(pGameMap, nRow, nRow, nCol1) && LinkY(pGameMap, nRow, nRow2, nCol2))
				{
					Vertex vx1 = { nRow,nCol1,BLANK };
					Vertex vx2 = { nRow,nCol2,BLANK };
					PushVertex(vx1);
					PushVertex(vx2);
					return true;
				}
			}
		}
	}
	return false;
}



void CGameLogic::Clear(int pGameMap[][4], Vertex V1, Vertex V2)
{
	pGameMap[V1.row][V1.col]==BLANK;
	pGameMap[V2.row][V2.col] == BLANK;
}

int CGameLogic::GetVexPath(Vertex avPath[4])
{
	for (int i = 0; i < m_nVexNum; i++)
	{
		avPath[i] = m_avPath[i];
	}
	return m_nVexNum;
}