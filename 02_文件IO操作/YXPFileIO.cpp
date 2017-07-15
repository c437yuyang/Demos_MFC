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
bool YXPFileIO::FolderExists(const CString& s)
{
	DWORD attr;
	attr = GetFileAttributes(s);
	return (attr != (DWORD)(-1)) &&
		(attr & FILE_ATTRIBUTE_DIRECTORY);
}

bool YXPFileIO::FileExists(const CString& s)
{
	DWORD attr;
	attr = GetFileAttributes(s);
	return (attr != (DWORD)(-1)) &&
		(attr & FILE_ATTRIBUTE_ARCHIVE); //这样，隐藏的或者只读的都能检测到
}


// 递归创建目录（不能使用/，只能\\，带后不带后\\都可以)
// 如果目录已经存在或者创建成功返回TRUE  
bool YXPFileIO::SuperMkDir(const CString& path)
{
	CString P(path);
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
// 返回的是文件的全路径
void YXPFileIO::GetDirectoryFiles(const string &strFolder,
	vector<string> &strVecFileNames,
	bool OnlyFiles,
	bool OnlyDirectories,
	const string &extInclude, //指定只包含的后缀名，带.
	const string &extExclude) //指定要排除的后缀名，带.
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
	if (OnlyDirectories) return; //只检索目录的话就返回了
	//去掉不需要的后缀名文件
	if (!extInclude.empty())
	{
		for (auto path = strVecFileNames.begin(); path != strVecFileNames.end();)
		{
			if (!FileExists(A2W((path->c_str()))))
			{
				++path;
				continue; //不考虑目录
			}

			if (!CheckFileExt(*path, extInclude))
				path = strVecFileNames.erase(path);
			else
				++path;
		}
	}

	//去掉不需要的后缀名文件
	if (!extExclude.empty())
	{
		for (auto path = strVecFileNames.begin(); path != strVecFileNames.end();)
		{
			if (!FileExists(A2W((path->c_str()))))
			{
				++path;
				continue; //不考虑目录
			}

			if (CheckFileExt(*path, extExclude))
				path = strVecFileNames.erase(path);
			else
				++path;
		}
	}

}

//后面一定要再检查返回值是否为空!,操作还是会继续的
CString YXPFileIO::BrowseFolder(const HWND owner)
{

	TCHAR wchPath[MAX_PATH];     //存放选择的目录路径 

	ZeroMemory(wchPath, sizeof(wchPath));
	BROWSEINFO bi;
	bi.hwndOwner = owner;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = wchPath;
	bi.lpszTitle = _T("请选择需要打开的目录：");
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	//弹出选择目录对话框
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);
	CString cStrPath;
	if (lp && SHGetPathFromIDList(lp, wchPath))
	{
		cStrPath.Format(_T("%s"), wchPath);//转为Cstring类型
	}

	return cStrPath;
}

void YXPFileIO::DeleteDirectory(const std::string path, bool delFolder)
{
	USES_CONVERSION;
	if (path.empty() || !FolderExists(A2W(path.c_str()))) return;
	vector<string> files;
	GetDirectoryFiles(path, files);
	if (!files.empty())
		for (int i = 0; i != files.size(); ++i)
			DeleteFileA(files[i].c_str());
	if (delFolder)
		RemoveDirectoryA(path.c_str());
}

std::string YXPFileIO::GetFileNameNoPath(const std::string &filename) //只支持\\的目录
{
	int pos = filename.rfind("\\");
	return filename.substr(pos + 1, filename.length() - pos);
}
std::string YXPFileIO::GetFileNameNoExt(const std::string &filename) //只判断.的位置，不会去除路径
{
	int pos = filename.rfind(".");
	return filename.substr(0, pos);
}
std::string YXPFileIO::GetFileNameExt(const std::string &filename) //返回带.的
{
	int pos = filename.rfind(".");
	return filename.substr(pos, filename.length() - pos);
}

bool YXPFileIO::CheckFileExt(const std::string& Path, const std::string &ext)
{
	if (Path.empty() || ext.empty()) return false;
	string ext_src = GetFileNameExt(Path);

	string ext_dst(ext);

	std::transform(ext_src.begin(), ext_src.end(), ext_src.begin(), ::tolower); //转换成小写
	std::transform(ext_dst.begin(), ext_dst.end(), ext_dst.begin(), ::tolower); //转换成小写

	if (ext_dst.compare(ext_src)) return false;
	return true;

}