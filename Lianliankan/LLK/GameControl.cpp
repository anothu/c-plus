#include "stdafx.h"
#include "GameControl.h"
#include"global.h"

int  CGameControl::s_nRows = 10;
int CGameControl::s_nCols = 16;
int CGameControl::s_nPicNum = 20;

CGameControl::CGameControl()
{
}


CGameControl::~CGameControl()
{
}

void CGameControl::StartGame()
{
	CGameLogic gameLogic;
	//m_PGameMap=gameLogic.InitMap();
	gameLogic.InitMap(m_PGameMap);
}

int CGameControl::GetElement(int nRow, int nCol)
{
	return m_PGameMap[nRow][nCol];
}

void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_svSelFst.row = nRow;
	m_svSelFst.col = nCol;
}
void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_svSelSec.row = nRow;
	m_svSelSec.col = nCol;
}

bool CGameControl::Link(Vertex avPath[4], int &m_nVexNum)
{

	//判断两个点是否连通
	if (m_svSelFst.row == m_svSelSec.row && m_svSelFst.col == m_svSelSec.col)
	{
		return false;
	}
	if (m_PGameMap[m_svSelFst.row][m_svSelFst.col] != m_PGameMap[m_svSelSec.row][m_svSelSec.col])
	{
		return false;
	}
	CGameLogic gameLogic;
	if (gameLogic.IsLink(m_PGameMap, m_svSelFst, m_svSelSec))
	{

		gameLogic.Clear(m_PGameMap, m_svSelFst, m_svSelSec);

		avPath[0] = m_svSelFst;
		avPath[1] = m_svSelSec;
		m_nVexNum = gameLogic.GetVexPath(avPath);
		return true;
	}
	return false;
}



