// 06_02_DllDemo2.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "06_02_DllDemo2.h"


// 这是导出变量的一个示例
MY06_02_DLLDEMO2_API int nMy06_02_DllDemo2=0;

// 这是导出函数的一个示例。
MY06_02_DLLDEMO2_API int fnMy06_02_DllDemo2(void)
{
    return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 06_02_DllDemo2.h
CMy06_02_DllDemo2::CMy06_02_DllDemo2()
{
    return;
}
