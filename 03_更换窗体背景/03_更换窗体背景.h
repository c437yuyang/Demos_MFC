
// 03_更换窗体背景.h : 03_更换窗体背景 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CMy03_更换窗体背景App:
// 有关此类的实现，请参阅 03_更换窗体背景.cpp
//

class CMy03_更换窗体背景App : public CWinAppEx
{
public:
	CMy03_更换窗体背景App();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy03_更换窗体背景App theApp;
