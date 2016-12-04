#pragma once
#include "IModel.h"

#include "cFileView.h"
//#include "cOptionBarView.h"
//#include "cStatusView.h"
#include <regex>
#include <vector>
#include "RegexSearch.h"

class FileListModel : public IModel
{
private:
	//WORD Folder;
	//BOOL Recursive;
	RegexSearch regSearch;
	std::regex RegSearch;
	std::vector<IView*> viewVec;
	virtual void Notify();
	virtual void Update();
	
	

public:
	virtual void ScanFile();
	std::vector<FileInfo> data;
	FileListModel(int argc, char* argv[]);
	~FileListModel();

	void Attach(IView* view);
};