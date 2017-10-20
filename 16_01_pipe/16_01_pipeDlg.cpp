
// 16_01_pipeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "16_01_pipe.h"
#include "16_01_pipeDlg.h"
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


// CMy16_01_pipeDlg 对话框



CMy16_01_pipeDlg::CMy16_01_pipeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY16_01_PIPE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy16_01_pipeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy16_01_pipeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy16_01_pipeDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMy16_01_pipeDlg 消息处理程序

BOOL CMy16_01_pipeDlg::OnInitDialog()
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
	SetDlgItemTextW(IDC_EDITCMD, _T("ipconfig.exe"));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy16_01_pipeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy16_01_pipeDlg::OnPaint()
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
HCURSOR CMy16_01_pipeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy16_01_pipeDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemTextW(IDC_EDITRESULT, _T(""));
	CString               m_Host;
	CString               strCmd;
	GetDlgItemText(IDC_EDITCMD,strCmd);
	m_Host = _T("c:\\windows\\system32\\") + strCmd;  //strCmd = "ipconfig.exe"  

													  //创建管道  
	HANDLE                   hReadPipe;
	HANDLE                   hWritePipe;
	SECURITY_ATTRIBUTES      sat;                            //安全属性结构  
	sat.nLength = sizeof(SECURITY_ATTRIBUTES);  //结构体大小  
	sat.bInheritHandle = true;                         //指出安全描述符的对象能否被新进程继承  
	sat.lpSecurityDescriptor = NULL;                         //安全描述符,NULL: 使用默认的   
	if (!CreatePipe(&hReadPipe, &hWritePipe, &sat, NULL))
	{
		MessageBox(_T("Create Pipe Error!"));
		return;
	}

	//创建进程  
	STARTUPINFO                 startupinfo;             //进程信息  
	PROCESS_INFORMATION   pinfo;
	startupinfo.cb = sizeof(STARTUPINFO); //结构体大小   
	GetStartupInfo(&startupinfo);                  //获取当前进程的信息  
	startupinfo.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	startupinfo.hStdError = hWritePipe;
	startupinfo.hStdOutput = hWritePipe;
	startupinfo.wShowWindow = SW_HIDE;
	if (!CreateProcess(NULL, m_Host.GetBuffer(), NULL, NULL,
		TRUE, NULL, NULL, NULL, &startupinfo, &pinfo))
	{
		MessageBox(_T("create process error!"));
		return;
	}
	CloseHandle(hWritePipe); //父进程关闭写端

	//获取管道信息  
	BYTE       buffer[1024];
	DWORD    byteRead;
	while (true)
	{
		RtlZeroMemory(buffer, 1024);
		if (ReadFile(hReadPipe, buffer, 1023, &byteRead, NULL) == NULL) //如果读的返回空了就代表写端已经关闭并且读完了
		{
			break;
		}
		CString str(buffer);
		CString preTxt;
		GetDlgItemText(IDC_EDITRESULT, preTxt);
		SetDlgItemTextW(IDC_EDITRESULT, preTxt + str);
	
	}
	CloseHandle(hReadPipe);
	m_Host.ReleaseBuffer();

}
