// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <iostream>
using namespace std;


//DllMain函数是DLL模块的默认入口点。当Windows加载DLL模块时调用这一函数。
//系统首先调用全局对象的构造函数，然后调用全局函数DLLMain。
//DLLMain函数不仅在将DLL链接加载到进程时被调用，在DLL模块与进程分离时（以及其它时候）也被调用。

//APIENTRY声明DLL函数入口点
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		cout << "DLL_PROCESS_ATTACH" << endl;
		break;
	case DLL_THREAD_ATTACH:
		cout << "DLL_THREAD_ATTACH" << endl;
		break;
	case DLL_THREAD_DETACH:
		cout << "DLL_THREAD_DETACH" << endl;
		break;
	case DLL_PROCESS_DETACH:
		cout << "DLL_PROCESS_DETACH" << endl;
		break;
	}
	return TRUE;
}

//如果程序员没有为DLL模块编写一个DLLMain函数，
//系统会从其它运行库中引入一个不做任何操作的缺省DLLMain
//函数版本。在单个线程启动和终止时，DLLMain函数也被调用。