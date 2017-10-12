
// 15_01_mmap_readDlg.h : 头文件
//

#pragma once


// CMy15_01_mmap_readDlg 对话框
class CMy15_01_mmap_readDlg : public CDialogEx
{
// 构造
public:
	CMy15_01_mmap_readDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY15_01_MMAP_READ_DIALOG };
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

public:
	HANDLE m_hMapObject;//映射对象句柄
	LPTSTR  m_pszMapView;

	afx_msg void OnBnClickedBtnReadInfo();
};
