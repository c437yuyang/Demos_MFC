#include <iostream>


//总结:静态库的使用分为两步
//1.制作静态库，新建项目类型为静态库类型即可，然后生成.lib文件
//2.使用静态库,指定静态库路径(附加库目录)，指定附加依赖项，或者直接#pragma comment(lib,"xxx")
//也可以这时显式指定路径，都行，最终只要能找到路径就行了，然后是头文件，也是类似的，只要能找到就行。

#include "../06_03_LibDemo/libDemo.h"
#pragma comment(lib,"../Debug/06_03_LibDemo.lib")
int main() 
{
	int i = LibDemo1Func();

	std::cout << i << std::endl;
	system("pause");
	return 0;

}

