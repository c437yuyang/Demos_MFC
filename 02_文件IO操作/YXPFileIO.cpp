#include "stdafx.h"
#include "YXPFileIO.h"

using namespace std;

YXPFileIO::YXPFileIO()
{
}


YXPFileIO::~YXPFileIO()
{
}


//创建指定目录，其父目录必须存在
bool YXPFileIO::FindOrCreateDirectory(const char *pszPath)
{
	USES_CONVERSION;
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFileW(A2W(pszPath), &fd);
	while (hFind != INVALID_HANDLE_VALUE)
	{
		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			//::AfxMessageBox(_T("目录存在！"));
			return true;
		}
	}

	if (!::CreateDirectory(A2W(pszPath), NULL))
	{
		//char szDir[MAX_PATH];
		::AfxMessageBox(_T("创建目录失败"));
		return false;
	}
	else
	{
		return true;
		//::AfxMessageBox(_T("创建目录成功"));
	}
}



// 判断目录是否存在(/或\\都可以，带后不带后\\都可以)  
bool YXPFileIO::FolderExists(CString s)
{
	DWORD attr;
	attr = GetFileAttributes(s);
	return (attr != (DWORD)(-1)) &&
		(attr & FILE_ATTRIBUTE_DIRECTORY);
}


// 递归创建目录（不能使用/，只能\\，带后不带后\\都可以)
// 如果目录已经存在或者创建成功返回TRUE  
bool YXPFileIO::SuperMkDir(CString P)
{
	int len = P.GetLength();
	if (len < 2) return false;

	if ('\\' == P[len - 1])
	{
		P = P.Left(len - 1);
		len = P.GetLength();
	}
	if (len <= 0) return false;

	if (len <= 3)
	{
		if (FolderExists(P))return true;
		else return false;
	}

	if (FolderExists(P))return true;

	CString Parent;
	Parent = P.Left(P.ReverseFind('\\'));

	if (Parent.GetLength() <= 0)return false;

	bool Ret = SuperMkDir(Parent);

	if (Ret)
	{
		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.lpSecurityDescriptor = NULL;
		sa.bInheritHandle = 0;
		Ret = (CreateDirectory(P, &sa) == TRUE);
		return Ret;
	}
	else
		return false;
}


//取得指定文件夹下的文件及文件夹名称（不递归，只取一级目录），全部用\\，不能/，后面不要带\\,
void YXPFileIO::GetDirectoryFiles(const string &strFolder, vector<string> &strVecFileNames,const string &extInclude="",const string &extExclude="")
{
	strVecFileNames.clear();
	struct _finddata_t filefind;
	string  curr = strFolder + "\\*.*";
	int  done = 0;
	int  handle;
	if ((handle = _findfirst(curr.c_str(), &filefind)) == -1)
		return;
	string tempfolder = strFolder + "\\";
	while (!(done = _findnext(handle, &filefind)))
	{
		if (!strcmp(filefind.name, ".."))  //用此方法第一个找到的文件名永远是".."，所以需要单独判断
			continue;
		strVecFileNames.push_back(tempfolder + filefind.name);
	}
	_findclose(handle);
}