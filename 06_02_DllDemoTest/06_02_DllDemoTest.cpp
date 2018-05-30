// 06_02_DllDemoTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

#pragma region DLL引用示例
//一共要包含三个地方，一个是头文件，一个是.dll文件，一个是.lib文件
#include <DllDemo.h>
#pragma comment(lib,"06_01_DllDemo.lib")
#include <06_02_DllDemo2.h>
#pragma comment(lib,"06_02_DllDemo2.lib")
#include <Dll1.h>
#pragma comment(lib,"Dll1.lib")

//lib 文件选择在项目属性，链接器-常规-附加库目录
//.h 文件在项目属性，C\C++-常规-附件包含目录,有dllmain的不需要dllmain.cpp，只需要头文件
//dll 文件要在同一目录(可以更改，但通常的做法是这样)
#pragma endregion


#pragma region 查找Dll目录的次序：

//应用程序使用LoadLibrary显式链接，那么在这个函数的参数中可以指定DLL文件的完整路径。
//如果不指定路径，或是进行隐式链接，Windows将遵循下面的搜索顺序来定位DLL：
//1． 包含EXE文件的目录，
//2． 进程的当前工作目录，
//3． Windows系统目录，
//4． Windows目录，
//5． 列在Path环境变量中的一系列目录。
#pragma endregion

#pragma region 更改dll包含目录，一般都不用，就放exe相同目录最好
//方法一：
//
//选择当前工程，右击
//"Properties" -> "Configuration Properties" -> "Debugging"，
//在"Working Directory"设置dll的路径就可以了

//方法二，显示指定
//CString strDllPath = GetExePath() + _T("System");
//SetDllDirectory(strDllPath);

//方法三：设置项目的环境变量

#pragma endregion


#pragma region 一种简单的使用dll的方法，参考自键值offer的Utilities的做法，
//1.Dll部分不变
//2.使用的时候，直接在当前项目中添加引用，然后包含对应头文件即可。
//这个方法也就是少了一步lib文件的包含而已
//具体请看:Test_Reference2UseDll 解决方案
#pragma endregion



int main()
{
	int c = Add(1, 2); //可以看到，一个解决方案下面的，直接就能调试到断点
	int d = Sub(2, 1);
	cout << c << endl;

	CMy06_02_DllDemo2 dllClass; //由于这个dll里面有dllmain，可以看到attach和detatch
	int e = fnMy06_02_DllDemo2();
	
	AddClass clsAd; //不同解决方案的，需要联调直接F11进去就行了
	int f = clsAd.output(1, 2);



    return 0;
}

