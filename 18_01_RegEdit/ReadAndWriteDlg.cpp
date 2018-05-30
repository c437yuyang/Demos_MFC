
// ReadAndWriteDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ReadAndWrite.h"
#include "ReadAndWriteDlg.h"
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


// CReadAndWriteDlg 对话框



CReadAndWriteDlg::CReadAndWriteDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_READANDWRITE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReadAndWriteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CReadAndWriteDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CReadAndWriteDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CReadAndWriteDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CReadAndWriteDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CReadAndWriteDlg 消息处理程序

BOOL CReadAndWriteDlg::OnInitDialog()
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

void CReadAndWriteDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CReadAndWriteDlg::OnPaint()
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
HCURSOR CReadAndWriteDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//写文本和写数值类型的例子
void CReadAndWriteDlg::OnBnClickedButton1()
{
	HKEY hKey = nullptr;
	//创建成功,将得到hKey,一个注册表句柄,用于下面操作注册表
	if (ERROR_SUCCESS != RegCreateKey(HKEY_CURRENT_USER, TEXT("SoftWare\\Test"), &hKey))
	{
		AfxMessageBox(TEXT("创建注册表失败"));
		return;
	}
	//写入注册表 //类型  //名称 //字符个数
	//只能写入一个value
	if (ERROR_SUCCESS != RegSetValueA(hKey, "subkey", REG_SZ, "Test", 4)) //subkey是下面的文件夹了
	{
		AfxMessageBox(TEXT("写入注册表失败"));
		return;
	}
	if (hKey == nullptr)
	{
		return;
	}
	DWORD dwData = 100;
	LONG lRet = 0;
	//这个函数可以写入更多的Value                      //名称            //类型        //数据
	if (ERROR_SUCCESS != (lRet = RegSetValueEx(hKey, TEXT("other"), 0, REG_DWORD, (CONST BYTE*)&dwData, 4)))
	{
		AfxMessageBox(TEXT("写入注册表失败Ex"));
		return;
	}

	if (ERROR_SUCCESS != (lRet = RegSetValueExA(hKey, TEXT("SubValue1"), 0, REG_SZ, (CONST BYTE*)"abcdef", 6)))
	{
		AfxMessageBox(TEXT("写入注册表失败Ex"));
		return;
	}

	AfxMessageBox(TEXT("写入注册表成功!"));
	RegCloseKey(hKey);
}



//读数值类型的例子
void CReadAndWriteDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	LONG lValue = 0;
	//先读取数据的长度
	RegQueryValue(HKEY_CURRENT_USER, TEXT("SoftWare\\Test"), nullptr, &lValue);  //读默认值
	TCHAR *pBuf = new TCHAR[lValue];
	RegQueryValueA(HKEY_CURRENT_USER, TEXT("SoftWare\\Test"), pBuf, &lValue);
	AfxMessageBox(pBuf);

	HKEY hKey = nullptr;
	DWORD dwTpye = 0;
	DWORD dwValue = sizeof(DWORD);//这个大小一定要先求出来,否则会出错(234)
	LPDWORD dwData = new DWORD;//一定要分配内存,否则也会出错
	LONG lRet = 0;
	//打开注册表
	RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("SoftWare\\Test"), 0, KEY_ALL_ACCESS, &hKey);
	//RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("SoftWare\\Test"), &hKey);
	//读注册表                                          //valuename      //返回value类型 //数据缓存区 //缓存区大小
	if (ERROR_SUCCESS != (lRet = RegQueryValueEx(hKey, TEXT("other"), 0, &dwTpye, (LPBYTE)dwData, &dwValue)))
	{
		AfxMessageBox(TEXT("读取注册表失败!"));
		return;
	}
	AfxMessageBox(TEXT("读取注册表成功!"));
	CString s;
	s.Format(TEXT("data = %d"), *dwData);
	AfxMessageBox(s);
	delete dwData;


	
	


}

//读取文本类型值
void CReadAndWriteDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

	HKEY hKey = nullptr;
	DWORD dwTpye = REG_SZ;
	DWORD dwValue = 255;//大小要和缓冲区大小一致，不然会报错，直接写大一点就OK了
	LPDWORD dwData = new DWORD;//一定要分配内存,否则也会出错
	char buf[255];
	LONG lRet = 0;
	//打开注册表
	RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("SOFTWARE\\Slice\\Params\\SerialPort"), 0, KEY_ALL_ACCESS, &hKey);
	//RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("SoftWare\\Test"), &hKey);
	//读注册表                                          //valuename      //返回value类型 //数据缓存区 //缓存区大小
	if (ERROR_SUCCESS != (lRet = RegQueryValueExA(hKey, TEXT("PortName"), 0, &dwTpye, (LPBYTE)buf, &dwValue)))
	{
		AfxMessageBox(TEXT("读取注册表失败!"));
		return;
	}
	AfxMessageBox(TEXT("读取注册表成功!"));

	AfxMessageBox(buf);
	delete dwData;


}
