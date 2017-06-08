
// 01_布局管理的实现Dlg.h : 头文件
//

#pragma once

#pragma region AutoFit
/**
*  控件随窗口变化的控制单元
**/
typedef struct tagCONTROL
{
	CWnd*	m_pWnd;				//指向控件的指针
	CRect	m_rectWnd;			//控件所占区域
	int		m_nMoveXPercent,	//控件沿x轴移动的百分比
		m_nMoveYPercent,	//控件沿y轴移动的百分比
		m_nZoomXPercent,	//控件沿x轴缩放的百分比
		m_nZoomYPercent;	//控件沿y轴缩放的百分比
}ControlInfo, *lpControlInfo;

typedef		CArray<lpControlInfo>	CTRLLIST;	//控件的适配信息表
#pragma endregion



// CMy01_布局管理的实现Dlg 对话框
class CMy01_布局管理的实现Dlg : public CDialogEx
{
	// 构造
public:
	CMy01_布局管理的实现Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY01__DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


#pragma region AutoFit
public:
	~CMy01_布局管理的实现Dlg();

	void	SetMinSize(int nWidth, int nHeight);
	void	FreeCtrlInfoList();
	void	MakeCtrlFit(CWnd* pWnd, int nMoveXPercent = 0, int nMoveYPercent = 0, int nZoomXPercent = 0, int nZoomYPercent = 0);
	void	CancelCtrlFit(HWND hWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);

	int			m_nWinWidth,		//窗口的宽度
				m_nWinHeight;		//窗口的高度
	POINT		m_ptMinTrackSize;	//窗口的最小大小
	CTRLLIST	m_listCtrlInfo;		//控件适配信息的数组  
#pragma endregion

	//afx_msg void OnNcPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnEnterSizeMove();
	afx_msg void OnExitSizeMove();
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
};
