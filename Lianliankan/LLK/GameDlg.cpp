// GameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include"global.h"
#include "GameDlg.h"
#include"GameControl.h"
#include "afxdialogex.h"


// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	m_ptGameTop.x = 50;
	m_ptGameTop.y = 50;

	m_sizeElem.cx = 40;
	m_sizeElem.cy = 40;

	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * 16;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * 10;

	m_bFirstPoint = TRUE;
}

CGameDlg::~CGameDlg()
{
}



void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_Start, &CGameDlg::OnClickedBtnStart)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CGameDlg 消息处理程序


void CGameDlg::InitBackground()
{	// TODO: 在此处添加实现代码.

	//加载BMP图片资源
	HANDLE Backbmp = ::LoadImage(NULL, _T("theme\\picture\\fruit_bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//获得当前对话框的视频内容
	CClientDC dc(this);

	//创建与视频内容兼容的内存DC
	m_dcBG.CreateCompatibleDC(&dc);

	//将位图资源选入DC
	m_dcBG.SelectObject(Backbmp);

	//初始化内存DC
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcMem.SelectObject(&bmpMem);

	//hu绘制背景到内存DC中
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);

	//设置窗口大小
	UpdateWindow();
}
BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	this->SetWindowTextW(_T("欢乐连连看　基本模式"));
	InitBackground();
	InitElement();
	UpdateWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0,0,800, 600, &m_dcMem, 0, 0, SRCCOPY);

}

void CGameDlg::UpdateWindow()
{
	CRect rtWin;
	CRect rtClient;
	GetWindowRect(rtWin);
	GetClientRect(rtClient);

	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtWin.Height();

	MoveWindow(0, 0, 800+ nSpanWidth, 600 + nSpanHeight);

	CenterWindow();
}
void CGameDlg::InitElement() {

	CClientDC dc(this);

	//加载BMP图片资源
	HANDLE Elmbmp = ::LoadImage(NULL, _T("theme\\picture\\fruit_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_dcElm.CreateCompatibleDC(&dc);
	m_dcElm.SelectObject(Elmbmp);

	//掩码图加载
	HANDLE Maskbmp = ::LoadImage(NULL, _T("theme\\picture\\fruit_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(Maskbmp);


}

void CGameDlg::OnClickedBtnStart()
{
	// TODO: 在此添加控件通知处理程序代码
	m_gameControl.StartGame();
	UpdateMap();
}

void CGameDlg::UpdateMap()
{
	// TODO: 在此处添加实现代码.

	//计算图片的顶点坐标与图片大小
	int nTop = m_ptGameTop.y;
	int nLeft = m_ptGameTop.x;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	//m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top,
	//m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);

	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{

			int nElemVal = m_gameControl.GetElement(i, j);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, nElemVal * nElemH, SRCPAINT);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElm, 0, nElemVal * nElemH, SRCAND);

		}
	}
	Invalidate(FALSE);
}

void CGameDlg::DrawTipFrame(int nRow, int nCol) {
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);
}

void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;
	if (nRow > 3 || nCol > 3)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	if (m_bFirstPoint)
	{
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetFirstPoint(nRow, nCol);
	}
	else
	{
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetSecPoint(nRow, nCol);
		Vertex avPath[4];
		int m_nVexNum;
		if (m_gameControl.Link(avPath, m_nVexNum))
		{
			DrawTipLine(avPath, m_nVexNum);
			//消除
			UpdateMap();
		}
		Sleep(200);
		InvalidateRect(m_rtGameRect, FALSE);

	}
	m_bFirstPoint = !m_bFirstPoint;
}

void CGameDlg::DrawTipLine(Vertex avPath[4], int nVexnum)
{

	CClientDC dc(this);

	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));


	CPen* pOldPen = dc.SelectObject(&penLine);

	dc.MoveTo(m_ptGameTop.x + avPath[0].col * m_sizeElem.cx + m_sizeElem.cx / 2,m_ptGameTop.y + avPath[0].row * m_sizeElem.cy + m_sizeElem.cy / 2);

	for (int i = 0; i < nVexnum - 1; i++)
	{

		dc.LineTo(m_ptGameTop.x + avPath[i + 1].col * m_sizeElem.cx + m_sizeElem.cx / 2,m_ptGameTop.y + avPath[i + 1].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}

	dc.SelectObject(pOldPen);
}



