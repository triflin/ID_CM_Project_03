#pragma once
#include "FileInfo.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <locale>
#include <filesystem>
#include <vector>


class RegexSearch {
public:
	std::tr2::sys::path folder = ".";
	std::string arg = "";
	unsigned int extCount = 0;
	unsigned int fileCount = 0;
	unsigned long long fileSize = 0;
	unsigned int extWidth = 10;
	unsigned int countWidth = 10;
	unsigned int sizeWidth = 10;
	std::vector<FileInfo> results;
	FileInfo newFile;
	bool isRecusive = false;

	RegexSearch(int argc, char* argv[]);
	~RegexSearch();

	std::vector<FileInfo> RegexSearch::fileInfoVec(int argc, char* argv[]);

	void RegexSearch::scan(std::tr2::sys::path const& f, std::regex regArg);

	void RegexSearch::rscan(std::tr2::sys::path const& f, std::regex regArg);
};
