
// 13_skin++_demo.h : 13_skin++_demo 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include <string>

// CMy13_skin_demoApp:
// 有关此类的实现，请参阅 13_skin++_demo.cpp
//

class CMy13_skin_demoApp : public CWinApp
{
public:
	CMy13_skin_demoApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()


	
	void SetSkin(std::string strSkinFile);

	static DWORD ThreadKill(LPVOID lp);
};

extern CMy13_skin_demoApp theApp;
