#pragma once
#include <io.h>
#include <string>
#include <vector>
#include <algorithm>

//所有调用windows API的函数返回的都是\\
//全部使用std::string,不使用CString
//所有操作使用使用Ansi版本
class YXPFileIO
{
public:
	YXPFileIO();
	~YXPFileIO();


	//TODO:GetDirectoryFiles增加排序选择

public:
	static bool FindOrMkDir(const std::string& pszPath);
	static bool FolderExists(const std::string& s);

	static bool FileExists(const std::string& s);
	static bool RecurMkDir(const std::string& path);
	static void GetDirectoryFiles(const std::string &strFolder,
		std::vector<std::string> &strVecFileNames,
		bool OnlyFiles = false,
		bool OnlyDirectories = false,
		const std::string &extInclude = "",
		const std::string &extExclude = "");
	static std::string BrowseFile(const std::string strFilter = "Images (*.jpg;*.png)\0*.jpg;*.png\0All (*.*)\0*.*\0\0", bool isOpen = true);

	static std::string YXPFileIO::BrowseFolder(const std::string & title = "请选择要打开的目录", const HWND owner = NULL);
	static void DeleteDirectory(const std::string path, bool deleteFolder = false);
	static std::string GetFileNameNoPath(const std::string &filename); //只支持\\的目录

	static std::string GetFileNameNoExt(const std::string &filename); //只判断.的位置，不会去除路径
	static std::string GetFileNameExt(const std::string &filename);
	static bool CheckFileExt(const std::string& Path, const std::string &ext);
	static bool Rename(const std::string &path, const std::string &dst, bool IsExistReplace = false);
	static std::string GetAppPath();
	static bool CopyDirFiles(const std::string&src, const std::string &dst, bool IsExistReplace = false);
};

