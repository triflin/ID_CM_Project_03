#pragma once
#include <string>

class FileInfo {
private:

public:
	FileInfo();
	~FileInfo();

	std::string root_ = "";
	std::string folderName_ = "";
	std::string fileName_ = "";
	unsigned int fileCount_ = 0;
	unsigned long long fileSize_ = 0;
};