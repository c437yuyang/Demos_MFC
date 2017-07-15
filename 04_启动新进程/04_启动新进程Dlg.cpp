
// 04_启动新进程Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "04_启动新进程.h"
#include "04_启动新进程Dlg.h"
#include "afxdialogex.h"

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


// CMy04_启动新进程Dlg 对话框



CMy04_启动新进程Dlg::CMy04_启动新进程Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY04__DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy04_启动新进程Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy04_启动新进程Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CREATEPROCESS, &CMy04_启动新进程Dlg::OnBnClickedBtnCreateprocess)
END_MESSAGE_MAP()


// CMy04_启动新进程Dlg 消息处理程序

BOOL CMy04_启动新进程Dlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy04_启动新进程Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy04_启动新进程Dlg::OnPaint()
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
HCURSOR CMy04_启动新进程Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void StartProcess(LPCTSTR szCmdLine);
void CMy04_启动新进程Dlg::OnBnClickedBtnCreateprocess()
{
	// TODO: 在此添加控件通知处理程序代码

	//STARTUPINFO si;
	//PROCESS_INFORMATION pi;

	//ZeroMemory(&si, sizeof(si));
	//si.cb = sizeof(si);
	////si.wShowWindow = SW_HIDE; //default is SW_SHOW
	//ZeroMemory(&pi, sizeof(pi));
	//LPTSTR szCmdline = _tcsdup(TEXT("calc.exe"));

	//// Start the child process. 
	//if (!CreateProcess(NULL,   // No module name (use command line)
	//	szCmdline,        // Command line
	//	NULL,           // Process handle not inheritable
	//	NULL,           // Thread handle not inheritable
	//	FALSE,          // Set handle inheritance to FALSE
	//	0,              // No creation flags
	//	NULL,           // Use parent's environment block
	//	NULL,           // Use parent's starting directory 
	//	&si,            // Pointer to STARTUPINFO structure
	//	&pi)           // Pointer to PROCESS_INFORMATION structure
	//	)
	//{
	//	printf("CreateProcess failed (%d).\n", GetLastError());
	//	return;
	//}

	//// Wait until child process exits.
	////WaitForSingleObject(pi.hProcess, INFINITE);

	//// Close process and thread handles. 
	//CloseHandle(pi.hProcess);
	//CloseHandle(pi.hThread);
	//delete[] szCmdline; //_tcsdup是堆上分配的内存

	StartProcess(_T("Calc.exe"));
}


void StartProcess(LPCTSTR cmdLine)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	//si.wShowWindow = SW_HIDE; //default is SW_SHOW
	ZeroMemory(&pi, sizeof(pi));
	LPTSTR szCmdline = _tcsdup(cmdLine);

	// Start the child process. 
	if (!CreateProcess(NULL,   // No module name (use command line)
		szCmdline,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		AfxMessageBox(_T("Error on createProcess,please check the path is right!"));
		delete[] szCmdline; //_tcsdup是堆上分配的内存
		return;
	}

	// Wait until child process exits.
	//WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	delete[] szCmdline; //_tcsdup是堆上分配的内存
}
