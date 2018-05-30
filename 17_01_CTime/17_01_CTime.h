
// 17_01_CTime.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CMy17_01_CTimeApp: 
// 有关此类的实现，请参阅 17_01_CTime.cpp
//

class CMy17_01_CTimeApp : public CWinApp
{
public:
	CMy17_01_CTimeApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CMy17_01_CTimeApp theApp;