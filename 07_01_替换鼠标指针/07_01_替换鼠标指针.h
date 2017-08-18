
// 07_01_替换鼠标指针.h : 07_01_替换鼠标指针 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CMy07_01_替换鼠标指针App:
// 有关此类的实现，请参阅 07_01_替换鼠标指针.cpp
//

class CMy07_01_替换鼠标指针App : public CWinAppEx
{
public:
	CMy07_01_替换鼠标指针App();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy07_01_替换鼠标指针App theApp;
