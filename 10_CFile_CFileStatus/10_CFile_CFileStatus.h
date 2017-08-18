
// 10_CFile_CFileStatus.h : 10_CFile_CFileStatus 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CMy10_CFile_CFileStatusApp:
// 有关此类的实现，请参阅 10_CFile_CFileStatus.cpp
//

class CMy10_CFile_CFileStatusApp : public CWinAppEx
{
public:
	CMy10_CFile_CFileStatusApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy10_CFile_CFileStatusApp theApp;
