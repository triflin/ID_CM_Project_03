#pragma once
#include "ThickWrapper.h"
#include "IView.h"
#include "cFileView.h"
#include "cOptionBarView.h"
#include "cStatusView.h"
#include "FileListModel.h"
#include <vector>

class Controller
{
private:
	cFileView fileView;
	cOptionBarView optionView;
	cStatusView statusView;
	FileListModel fileModel;

public:
	Controller(ThickWrapper thick, int argc, char* argv[]);
	~Controller();
};