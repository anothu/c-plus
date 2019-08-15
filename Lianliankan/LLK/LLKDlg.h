
// LLKDlg.h : header file
//

#pragma once


// CLLKDlg dialog
class CLLKDlg : public CDialogEx
{
// Construction
public:
	CLLKDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LLK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CDC m_dcMem;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void InitBackground();
	afx_msg void OnClickedBtnBasic();//BN_CLICKED消息响应函数
};
