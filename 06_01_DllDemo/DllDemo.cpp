#include "DllDemo.h"
DLLDEMO_API int __stdcall Add(int a, int b) 
{
	return a + b;
}

DLLDEMO_API int __stdcall Sub(int a, int b)
{
	return a - b;
}