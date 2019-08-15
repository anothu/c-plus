#pragma once

#include"GameControl.h"

#include"global.h"
// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGameDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	CDC m_dcMem;			//内存DC
	CDC m_dcBG;				//背景DC
	CDC m_dcElm;			//元素内存DC
	CDC m_dcMask;			//掩码内存DC
	CPoint m_ptGameTop;		//起始点坐标
    CSize m_sizeElem;		//图片元素大小
    CRect m_rtGameRect;     //游戏区域的大小
    CGameControl m_gameControl; //游戏控制类
	bool m_bFirstPoint;
	Vertex m_avPath[4];
	int m_nVexNum;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();//窗口初始化函数
	afx_msg void OnPaint();//WM_PAINT消息函数
	afx_msg void OnClickedBtnStart();
	void InitBackground();
	void InitElement();
	void UpdateWindow();//更新界面
	void UpdateMap();
	

protected:
	void DrawTipLine(Vertex avPath[4], int nVexnum);
	void DrawTipFrame(int nRow, int nCol);

public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
