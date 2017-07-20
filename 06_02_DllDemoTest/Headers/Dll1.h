#define DLL1_EXPORTS
#ifdef DLL1_EXPORTS
#define DLL1_API _declspec(dllexport)
#else
#define DLL1_API _declspec(dllimport)
#endif


DLL1_API int add(int a,int b);
DLL1_API int sub(int a,int b);


class DLL1_API AddClass
{
public:
	int output(int x,int y);
};

// _declspec(dllimport) int add(int a,int b);
// _declspec(dllimport) int sub(int a,int b);