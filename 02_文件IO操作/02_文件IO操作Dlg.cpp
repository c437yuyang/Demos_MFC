
// 02_文件IO操作Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "02_文件IO操作.h"
#include "02_文件IO操作Dlg.h"
#include "afxdialogex.h"
#include "YXPFileIO.h"
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


// CMy02_文件IO操作Dlg 对话框



CMy02_文件IO操作Dlg::CMy02_文件IO操作Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY02_IO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy02_文件IO操作Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy02_文件IO操作Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy02_文件IO操作Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy02_文件IO操作Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy02_文件IO操作Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMy02_文件IO操作Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMy02_文件IO操作Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMy02_文件IO操作Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMy02_文件IO操作Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CMy02_文件IO操作Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CMy02_文件IO操作Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CMy02_文件IO操作Dlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CMy02_文件IO操作Dlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CMy02_文件IO操作Dlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CMy02_文件IO操作Dlg::OnBnClickedButton13)
END_MESSAGE_MAP()


// CMy02_文件IO操作Dlg 消息处理程序

BOOL CMy02_文件IO操作Dlg::OnInitDialog()
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

void CMy02_文件IO操作Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy02_文件IO操作Dlg::OnPaint()
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
HCURSOR CMy02_文件IO操作Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CMy02_文件IO操作Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	//bool b = YXPFileIO::FindOrCreateDirectory("E:\\a\\我们");


	bool b1 = YXPFileIO::RecurMkDir("E:\\a1\\b1");
	 b1 = YXPFileIO::RecurMkDir("E:\\a1\\我们");

	//bool b2 = YXPFileIO::SuperMkDir(_T("E:\\a2\\b2\\"));
	//bool b3 = YXPFileIO::SuperMkDir(_T("E:/a3/b3")); //不能用/

}


void CMy02_文件IO操作Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	bool b = YXPFileIO::FolderExists(("E:\\caffe-windows\\"));
	bool b2 = YXPFileIO::FolderExists(("E:\\caffe-windows"));
	bool b3 = YXPFileIO::FolderExists(("E:/caffe-windows/"));
	bool b1 = YXPFileIO::FolderExists(("E:\\caffe-windows1\\"));//false
	bool b4 = YXPFileIO::FolderExists(("E:\\"));
}


void CMy02_文件IO操作Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	using namespace std;
	vector<string> vecFiles;
	//YXPFileIO::GetDirectoryFiles("E:\\caffe-windows", vecFiles, true);//拿到的文件夹不带\\，找所有文件

	//
	//YXPFileIO::GetDirectoryFiles("E:\\caffe-windows\\", vecFiles, false, true); //后面可以带\\(修复了)，找所有文件夹
	//YXPFileIO::GetDirectoryFiles("E:\\caffe-windows\\", vecFiles, true, true); //文件夹+文件

	////下面错误用法
	//YXPFileIO::GetDirectoryFiles("E:/caffe-windows/", vecFiles);//也不要用/，后面有个拼接主要是，用的\\进行的拼接

	string path(YXPFileIO::BrowseFolder("请选择要打开的目录",this->m_hWnd));
	YXPFileIO::GetDirectoryFiles((path), vecFiles, true, false, ".docx");
	YXPFileIO::GetDirectoryFiles((path), vecFiles, true, false, "",".rar");
	YXPFileIO::GetDirectoryFiles((path), vecFiles, false, false, "", ".rar");


}


void CMy02_文件IO操作Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码


//#define FILE_SHARE_READ                 0x00000001  
//#define FILE_SHARE_WRITE                0x00000002  
//#define FILE_SHARE_DELETE               0x00000004  
//#define FILE_ATTRIBUTE_READONLY             0x00000001  
//#define FILE_ATTRIBUTE_HIDDEN               0x00000002  
//#define FILE_ATTRIBUTE_SYSTEM               0x00000004  
//#define FILE_ATTRIBUTE_DIRECTORY            0x00000010  
//#define FILE_ATTRIBUTE_ARCHIVE              0x00000020  
//#define FILE_ATTRIBUTE_DEVICE               0x00000040  
//#define FILE_ATTRIBUTE_NORMAL               0x00000080


	DWORD attr;
	CString path = _T("E:\\Libs_Cpp\\boost_1_64_0\\INSTALL");
	attr = GetFileAttributes(path);
	path = _T("E:\\Libs_Cpp\\boost_1_64_0\\test1.txt"); //通常文件就是FILE_ATTRIBUTE_ARCHIVE,如果在这之上有隐藏的话就或FILE_ATTRIBUTE_HIDDEN，就是加，有只读类似
	attr = GetFileAttributes(path);
	path = _T("E:\\Libs_Cpp\\boost_1_64_0\\test2.txt");
	attr = GetFileAttributes(path);
	path = _T("E:\\Libs_Cpp\\boost_1_64_0\\test4.txt");
	attr = GetFileAttributes(path);

	path = _T("E:\\Libs_Cpp\\boost_1_64_0\\test5");
	attr = GetFileAttributes(path);
	path = _T("E:\\Libs_Cpp\\boost_1_64_0\\test5.txt"); //不存在就是-1
	attr = GetFileAttributes(path);

	bool b1 = (DWORD)-1 == attr;

	bool b = (attr != (DWORD)(-1)) &&
		(attr & FILE_ATTRIBUTE_DIRECTORY);
}


void CMy02_文件IO操作Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码

	string selectedFolder = YXPFileIO::BrowseFolder("",this->m_hWnd);
	MessageBox(CString(selectedFolder.c_str()));
}


void CMy02_文件IO操作Dlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	string selectedFolder = YXPFileIO::BrowseFolder("", this->m_hWnd);
	YXPFileIO::DeleteDirectory((selectedFolder),false);

}


void CMy02_文件IO操作Dlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	MessageBox(A2W(YXPFileIO::GetFileNameNoExt("E:\\DSD\\A.TXT").c_str()));
	MessageBox(A2W(YXPFileIO::GetFileNameNoExt("A.TXT").c_str()));
	MessageBox(A2W(YXPFileIO::GetFileNameNoPath("E:\\DSD\\A.TXT").c_str()));

}


void CMy02_文件IO操作Dlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;

	MessageBox(A2W(YXPFileIO::GetFileNameExt("E:\\DSD\\A.TXT").c_str()));

}


void CMy02_文件IO操作Dlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码

	MessageBox(YXPFileIO::CheckFileExt("A.txt",".TXT")?L"True":L"False");
	MessageBox(YXPFileIO::CheckFileExt("A.txt", ".txt") ? L"True" : L"False");
	MessageBox(YXPFileIO::CheckFileExt("A.txt", ".tx") ? L"True" : L"False");


}


void CMy02_文件IO操作Dlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码

	bool b = YXPFileIO::Rename("E:\\a","E:\\b");
	b = YXPFileIO::Rename("E:\\a", "E:\\b",true);

	//int i = rename("E:\\a", "E:\\b");

}


void CMy02_文件IO操作Dlg::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	
	AfxMessageBox(A2W(YXPFileIO::GetAppPath().c_str()));
}


void CMy02_文件IO操作Dlg::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码

	bool b = YXPFileIO::CopyDirFiles("E:\\a", "E:\\b", false);

}


void CMy02_文件IO操作Dlg::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码
	std::string str = YXPFileIO::BrowseFile();

}
