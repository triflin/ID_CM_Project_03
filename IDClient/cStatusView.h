#pragma once
#include "IView.h"
#include "ThickWrapper.h"
#include "FileListModel.h"
#include <vector>
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

class cStatusView : public IView
{
private:

	FileListModel& fileList;
	ThickWrapper& thick;
	virtual void Update();
	virtual void HasFocus() {}

public:
	cStatusView(ThickWrapper& _thick, FileListModel& fl);
	~cStatusView();
	void clearScreen();
	void Setup();
	void Draw();
	void Input();
	void Logic();
	void randFruit();
};