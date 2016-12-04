#include "FileListModel.h"
#include "XError.h"

FileListModel::FileListModel(int argc, char* argv[]) : regSearch(argc, argv)
{
	data = regSearch.fileInfoVec(argc, argv);
}


FileListModel::~FileListModel()
{

}

void FileListModel::Attach(IView* view)
{
	viewVec.push_back(view);
}

void FileListModel::Update() {

}

void FileListModel::Notify()
{
	for (auto& view : viewVec) {
		view->Update();
	}
}

void FileListModel::ScanFile() {
	
	Notify();
}
