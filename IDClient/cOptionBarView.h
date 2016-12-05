#pragma once
#include "IView.h"
#include "FileListModel.h"
#include "ThickWrapper.h"
#include <vector>

class cOptionBarView : public IView
{
private:
	FileListModel& fileList;
	ThickWrapper& thick;
	virtual void Update();
	virtual void HasFocus() {}

public:
	cOptionBarView(ThickWrapper& _thick, FileListModel& fl);
	~cOptionBarView();

	void Draw(ThickWrapper thick);
};