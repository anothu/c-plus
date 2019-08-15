#pragma once
#include"global.h"

class CGameLogic
{
protected:
	Vertex m_avPath[4];    //保存连接路径的起始点、拐点、终点
	int m_nVexNum;
protected:
	bool LinkInRow(int pGameMap[][4], Vertex V1, Vertex V2);
	bool LinkInCol(int pGameMap[][4], Vertex V1, Vertex V2);
	bool OneCornerLink(int pGameMap[][4], Vertex V1, Vertex V2);
	bool TwoCornerLink(int pGameMap[][4], Vertex V1, Vertex V2);
	bool LinkY(int pGameMap[][4], int nRow1, int nRow2, int nCol);
	bool LinkX(int pGameMap[][4], int nRow, int nCol1, int nCol2);
	void PushVertex(Vertex V);
	void PopVertex();

public:
	CGameLogic();
	~CGameLogic();
public:
	//int** InitMap();
	void InitMap(int pGameMap[][4]);
	//void ReleaseMap(int **&pGameMap);
	void Clear(int pGameMap[][4], Vertex v1, Vertex v2);
	bool IsLink(int pGameMap[][4], Vertex v1, Vertex v2);
	int GetVexPath(Vertex avPath[4]);


};