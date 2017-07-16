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
//就算用A版本不用W版本，也是支持中文的
bool YXPFileIO::FindOrMkDir(const std::string& pszPath)
{
	USES_CONVERSION;
	WIN32_FIND_DATAA fd;
	HANDLE hFind = ::FindFirstFileA(pszPath.c_str(), &fd);
	while (hFind != INVALID_HANDLE_VALUE)
	{
		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			return true;
	}

	if (!::CreateDirectoryA(pszPath.c_str(), NULL))
	{
		::AfxMessageBox(_T("创建目录失败"));
		return false;
	}
	else
		return true;
}



// 判断目录是否存在(/或\\都可以，带后不带后\\都可以)  
bool YXPFileIO::FolderExists(const std::string& s)
{
	DWORD attr;
	attr = GetFileAttributesA(s.c_str());
	return (attr != (DWORD)(-1)) &&
		(attr & FILE_ATTRIBUTE_DIRECTORY);
}


bool YXPFileIO::FileExists(const std::string& s)
{
	DWORD attr;
	attr = GetFileAttributesA(s.c_str());
	return (attr != (DWORD)(-1)) &&
		(attr & FILE_ATTRIBUTE_ARCHIVE); //这样，隐藏的或者只读的都能检测到
}

// 递归创建目录（不能使用/，只能\\，带后不带后\\都可以)
// 如果目录已经存在或者创建成功返回TRUE  
bool YXPFileIO::RecurMkDir(const std::string& path)
{
	string p(path);
	int len = p.length();
	if (len < 2) return false;

	if ('\\' == p[len - 1])
	{
		p = p.substr(0, len - 1);
		len = p.length();
	}
	if (len <= 0) return false;

	if (len <= 3)
	{
		if (FolderExists(p)) return true;
		else return false;
	}

	if (FolderExists(p))return true;

	string parDir = p.substr(0, p.rfind('\\'));

	if (parDir.length() <= 0)return false;

	bool Ret = RecurMkDir(parDir);

	if (Ret)
	{
		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.lpSecurityDescriptor = NULL;
		sa.bInheritHandle = 0;
		Ret = (CreateDirectoryA(p.c_str(), &sa) == TRUE);
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
			if (FileExists(tempfolder + filefind.name))
			{
				strVecFileNames.push_back(tempfolder + filefind.name);
			}
		}
		else if (OnlyDirectories)
		{
			CString temp = A2W((tempfolder + filefind.name).c_str());
			if (FileExists(tempfolder + filefind.name))
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
			if (!FileExists(path->c_str()))
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
			if (!FileExists(path->c_str()))
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
std::string YXPFileIO::BrowseFolder(const std::string & title, const HWND owner)
{
	//TCHAR wchPath[MAX_PATH];     //存放选择的目录路径 
	char path[MAX_PATH];
	ZeroMemory(path, sizeof(path));
	BROWSEINFOA bi;
	bi.hwndOwner = owner;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = path;
	bi.lpszTitle = title.c_str();
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	//弹出选择目录对话框
	LPITEMIDLIST lp = SHBrowseForFolderA(&bi);
	CString cStrPath;
	if (lp && SHGetPathFromIDListA(lp, path))
	{
		return path;
	}
	return "";

}

void YXPFileIO::DeleteDirectory(const std::string path, bool delFolder)
{
	if (path.empty() || !FolderExists(path.c_str())) return;
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


//重命名目录或文件，IsExistReplace指定存在时会否替换
bool YXPFileIO::Rename(const std::string &src, const std::string &dst, bool IsExistReplace)
{
	//文件不存在直接返回false
	if (!FileExists(src) && !FolderExists(src)) return false;
	if ((FileExists(dst) || FolderExists(dst)) && !IsExistReplace)
		return false;

	if (FileExists(dst) && IsExistReplace)
	{
		DeleteFileA(dst.c_str());
	}

	if (FolderExists(dst) && IsExistReplace)
	{
		DeleteDirectory(dst, true); //不能递归删除目录，只能删除含有文件的目录
	}


	//win sdk的rename函数说明:
	//1.目标文件名已经存在会返回-1失败
	//2.理所应当的可以跨目录
	//3.可以直接重命名目录，里面有文件也可以,当然同理目标目录已存在(无论有文件否)会报错
	return	rename(src.c_str(), dst.c_str()) < 0 ? false : true;
}

std::string YXPFileIO::GetAppPath()
{
	char exeFullPath[MAX_PATH];

	GetModuleFileNameA(NULL, exeFullPath, MAX_PATH);
	string pathName(exeFullPath);

	//返回值最后不带'\\'
	int index = pathName.rfind('\\');
	return pathName.substr(0, index);
}

//其实这些操作可以返回值返回为enum,更直观，光是返回false，太不清晰了
//要求dst目录必须已经存在,只拷贝文件
bool YXPFileIO::CopyDirFiles(const std::string & src, const std::string & dst, bool IsExistReplace)
{
	string dstPath(dst);
	if (!FolderExists(src) || dstPath.empty()) return false;

	if (dstPath[dstPath.length() - 1] == '\\')
	{
		dstPath = dstPath.substr(0, dstPath.length() - 1);
	}


	vector<std::string> srcFiles;

	GetDirectoryFiles(src, srcFiles,true);
	if (!IsExistReplace) //不进行替换的情况下，先检查有重复文件否,防止出现部分拷贝
	{
		vector<std::string> dstFiles;
		GetDirectoryFiles(dstPath, dstFiles, true);
		for (auto srcFile : srcFiles)
		{
			for (auto dstFile : dstFiles)
			{
				if (_stricmp(GetFileNameNoPath(srcFile).c_str(),
								GetFileNameNoPath(dstFile).c_str()) == 0)
					return false;
			}

		}
	}



	//CopyFile:
	//If the function succeeds, the return value is nonzero.
	//If the function fails, the return value is zero.To get extended error information, call GetLastError.
	for (auto it=srcFiles.begin();it!=srcFiles.end();++it)
	{
		if (!CopyFileA(it->c_str(), (dst +"\\"+ GetFileNameNoPath(*it)).c_str(), !IsExistReplace))
			return false;
	}


	return true;
}
