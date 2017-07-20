#pragma once
//该宏完成在dll项目内部使用__declspec(dllexport)导出  
//在dll项目外部使用时，用__declspec(dllimport)导入  
//宏DLL_IMPLEMENT在SimpleDLL.cpp中定义  

//为了去除对于VC运行库的依赖，在项目属性里面，使用静态MFC

#ifdef DLL_IMPLEMENT  
#define DLL_API __declspec(dllexport)  
#else  
#define DLL_API __declspec(dllimport)  
#endif 
#define DLLDEMO_API __declspec(dllexport)
extern "C" DLLDEMO_API int __stdcall Add(int a, int b); //添加Extern “C” 让函数名称正常，其他语言才能调用

extern "C" DLLDEMO_API int __stdcall Sub(int a, int b);