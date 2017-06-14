#pragma once
#include <io.h>
#include <string>
#include <vector>

class YXPFileIO
{
public:
	YXPFileIO();
	~YXPFileIO();


public:
	static bool FindOrCreateDirectory(const char *pszPath);
	static bool FolderExists(CString s);
	static bool FileExists(CString s);
	static bool SuperMkDir(CString P);
	static void GetDirectoryFiles(const std::string &strFolder,
									std::vector<std::string> &strVecFileNames,
									bool OnlyFiles = false,
									bool OnlyDirectories = false,
									const std::string &extInclude = "",
									const std::string &extExclude = "");

};

