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

bool YXPFileIO::FileExists(CString s)
{
	DWORD attr;
	attr = GetFileAttributes(s);
	return (attr != (DWORD)(-1)) &&
		(attr & FILE_ATTRIBUTE_ARCHIVE); //这样，隐藏的或者只读的都能检测到
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

//TODO:换成用CString，mfc里面就用CString，不要想那么多
//取得指定文件夹下的文件及文件夹名称（不递归，只取一级目录），全部用\\，不能/，后面可以带\\(修复了),
void YXPFileIO::GetDirectoryFiles(const string &strFolder,
	vector<string> &strVecFileNames,
	bool OnlyFiles,
	bool OnlyDirectories,
	const string &extInclude,
	const string &extExclude)
{
	USES_CONVERSION;
	if (OnlyFiles&&OnlyDirectories)  //如果两个都选中，那么就是所有文件，直接默认不选了
	{
		OnlyFiles = false;
		OnlyDirectories = false;
	}

	strVecFileNames.clear();
	struct _finddata_t filefind;
	string  curr = strFolder + "\\*.*";
	int  done = 0;
	int  handle;
	if ((handle = _findfirst(curr.c_str(), &filefind)) == -1)
		return;

	string tempfolder = strFolder;
	if (strFolder[strFolder.size() - 1] != '\\')
	{
		tempfolder += "\\";
	}

	while (!(done = _findnext(handle, &filefind)))
	{
		if (!strcmp(filefind.name, ".."))  //用此方法第一个找到的文件名永远是".."，所以需要单独判断
			continue;
		if (OnlyFiles)
		{
			//TODO::这里应该换一下不要用A2W,后面文件多了性能会很低
			CString temp = A2W((tempfolder + filefind.name).c_str());
			if (FileExists(temp))
			{
				strVecFileNames.push_back(tempfolder + filefind.name);
			}
		}
		else if (OnlyDirectories)
		{
			CString temp = A2W((tempfolder + filefind.name).c_str());
			if (FolderExists(temp))
			{
				strVecFileNames.push_back(tempfolder + filefind.name);
			}
		}
		else
		{
			strVecFileNames.push_back(tempfolder + filefind.name);
		}

	}
	_findclose(handle);
}