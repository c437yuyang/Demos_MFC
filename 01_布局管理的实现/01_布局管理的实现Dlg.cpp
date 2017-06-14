
// 01_布局管理的实现Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "01_布局管理的实现.h"
#include "01_布局管理的实现Dlg.h"
#include "afxdialogex.h"
#include <iostream>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy01_布局管理的实现Dlg 对话框



CMy01_布局管理的实现Dlg::CMy01_布局管理的实现Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY01__DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
#pragma region AutoFit
	m_ptMinTrackSize.x = 0;
	m_ptMinTrackSize.y = 0;
#pragma endregion

}

#pragma region AutoFit
CMy01_布局管理的实现Dlg::~CMy01_布局管理的实现Dlg()
{
	FreeCtrlInfoList();
}

void CMy01_布局管理的实现Dlg::SetMinSize(int nWidth, int nHeight)
{
	ASSERT(nWidth > 0);
	ASSERT(nHeight > 0);

	//设置窗口最小值
	m_ptMinTrackSize.x = nWidth;
	m_ptMinTrackSize.y = nHeight;
}

void CMy01_布局管理的实现Dlg::FreeCtrlInfoList()
{
	INT_PTR	nCount = m_listCtrlInfo.GetSize();

	for (int i = 0; i < nCount; i++)
	{
		lpControlInfo pCtrlInfo = m_listCtrlInfo.ElementAt(i);
		delete pCtrlInfo;
	}

	m_listCtrlInfo.RemoveAll();
}

void CMy01_布局管理的实现Dlg::MakeCtrlFit(CWnd* pWnd, int nMoveXPercent, int nMoveYPercent, int nZoomXPercent, int nZoomYPercent)
{
	ASSERT(pWnd);									//指针是否为空
	ASSERT(nMoveXPercent >= 0 && nMoveXPercent <= 100);	//nMoveXPercent值是否有效
	ASSERT(nMoveYPercent >= 0 && nMoveYPercent <= 100);	//nMoveXPercent值是否有效
	ASSERT(nZoomXPercent >= 0 && nZoomXPercent <= 100);	//nMoveXPercent值是否有效
	ASSERT(nZoomYPercent >= 0 && nZoomYPercent <= 100);	//nMoveXPercent值是否有效

	lpControlInfo	pCtrlInfo = new ControlInfo;	//创建结构指针

													//填充变量
	pCtrlInfo->m_pWnd = pWnd;
	pCtrlInfo->m_nMoveXPercent = nMoveXPercent;
	pCtrlInfo->m_nMoveYPercent = nMoveYPercent;
	pCtrlInfo->m_nZoomXPercent = nZoomXPercent;
	pCtrlInfo->m_nZoomYPercent = nZoomYPercent;

	pWnd->GetWindowRect(pCtrlInfo->m_rectWnd);
	ScreenToClient(&pCtrlInfo->m_rectWnd);

	m_listCtrlInfo.Add(pCtrlInfo);	//加入维护列表
}

void CMy01_布局管理的实现Dlg::CancelCtrlFit(HWND hWnd)
{
	INT_PTR	nCount = m_listCtrlInfo.GetSize();

	for (int i = 0; i < nCount; i++)
	{
		lpControlInfo pCtrlInfo = m_listCtrlInfo.ElementAt(i);
		if (pCtrlInfo->m_pWnd->GetSafeHwnd() == hWnd)
		{
			delete pCtrlInfo;
			m_listCtrlInfo.RemoveAt(i);

			break;
		}
	}
}

void CMy01_布局管理的实现Dlg::OnSize(UINT nType, int cx, int cy)
{
	//计算窗口宽度和高度的改变量
	int nIncrementX = cx - m_nWinWidth;
	int nIncrementY = cy - m_nWinHeight;

	INT_PTR	nCount = m_listCtrlInfo.GetSize();

	UINT	uFlags = SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOCOPYBITS;
	for (int i = 0; i < nCount; i++)
	{
		//获取变化控制系数
		int	nMoveXPercent = m_listCtrlInfo[i]->m_nMoveXPercent;
		int	nMoveYPercent = m_listCtrlInfo[i]->m_nMoveYPercent;
		int	nZoomXPercent = m_listCtrlInfo[i]->m_nZoomXPercent;
		int	nZoomYPercent = m_listCtrlInfo[i]->m_nZoomYPercent;

		CWnd*	pWndCtrl = m_listCtrlInfo[i]->m_pWnd;
		HWND	hWnd = pWndCtrl->GetSafeHwnd();
		if ((NULL != pWndCtrl) && IsWindow(hWnd))
		{
			int nLeft = m_listCtrlInfo[i]->m_rectWnd.left;
			int nTop = m_listCtrlInfo[i]->m_rectWnd.top;
			int nWidth = m_listCtrlInfo[i]->m_rectWnd.Width();
			int nHeight = m_listCtrlInfo[i]->m_rectWnd.Height();

			//设置新的位置参数
			nLeft += (nIncrementX*nMoveXPercent / 100);
			nTop += (nIncrementY*nMoveYPercent / 100);
			nWidth += (nIncrementX*nZoomXPercent / 100);
			nHeight += (nIncrementY*nZoomYPercent / 100);

			//  把控件移动到新位置
			pWndCtrl->MoveWindow(nLeft, nTop, nWidth, nHeight);
		}
	}
	Invalidate(TRUE);//强制刷新窗口，防止出现鬼影
	UpdateWindow(); //updateWindow必须和invalidate配合使用才能有效果
	CDialogEx::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
}

void CMy01_布局管理的实现Dlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//设置窗口的最小大小
	lpMMI->ptMinTrackSize = m_ptMinTrackSize;

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}

#pragma endregion



void CMy01_布局管理的实现Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy01_布局管理的实现Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_NCPAINT()
	ON_WM_ERASEBKGND()
	ON_WM_ENTERSIZEMOVE()
	ON_WM_EXITSIZEMOVE()
	ON_WM_NCCALCSIZE()
	ON_BN_CLICKED(IDOK, &CMy01_布局管理的实现Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMy01_布局管理的实现Dlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMy01_布局管理的实现Dlg 消息处理程序

BOOL CMy01_布局管理的实现Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
#pragma region AutoFit
	CRect	rectTemp;

	//获取客户区大小
	GetClientRect(rectTemp);
	//保存客户区信息
	m_nWinWidth = rectTemp.Width();
	m_nWinHeight = rectTemp.Height();
	//获取窗口大小
	GetWindowRect(rectTemp);
	//设置窗口最小值
	SetMinSize(rectTemp.Width(), rectTemp.Height());

	//适配控件
	MakeCtrlFit(GetDlgItem(IDC_BUTTON2), 33);
	MakeCtrlFit(GetDlgItem(IDC_BUTTON3), 66);
	MakeCtrlFit(GetDlgItem(IDC_BUTTON4), 100);

	MakeCtrlFit(GetDlgItem(IDC_EDIT1), 0, 0, 50, 50);
	MakeCtrlFit(GetDlgItem(IDC_EDIT2), 50, 0, 50, 50);
	MakeCtrlFit(GetDlgItem(IDC_EDIT3), 0, 50, 50, 50);
	MakeCtrlFit(GetDlgItem(IDC_PIC), 50, 50, 50, 50);

	MakeCtrlFit(GetDlgItem(IDOK), 100, 100);
	MakeCtrlFit(GetDlgItem(IDCANCEL), 100, 100);
#pragma endregion
	//InitConsoleWindow();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy01_布局管理的实现Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy01_布局管理的实现Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy01_布局管理的实现Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CMy01_布局管理的实现Dlg::OnNcPaint()
//{
//	// TODO: 在此处添加消息处理程序代码
//	// 不为绘图消息调用 CDialogEx::OnNcPaint()
//}


BOOL CMy01_布局管理的实现Dlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return CDialogEx::OnEraseBkgnd(pDC);
}


void CMy01_布局管理的实现Dlg::OnEnterSizeMove()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	cout << "OnEnterSizeMove" << endl;
	CDialogEx::OnEnterSizeMove();
}


void CMy01_布局管理的实现Dlg::OnExitSizeMove()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	cout << "OnExitSizeMove" << endl;

	CDialogEx::OnExitSizeMove();
}


void CMy01_布局管理的实现Dlg::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	cout << "OnNcCalcSize" << endl;

	CDialogEx::OnNcCalcSize(bCalcValidRects, lpncsp);
}


void CMy01_布局管理的实现Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	cout << "ok" << endl;
	//CDialogEx::OnOK();
}


void CMy01_布局管理的实现Dlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
