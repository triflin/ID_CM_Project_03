#include "cOptionBarView.h"
#include "XError.h"

cOptionBarView::cOptionBarView(ThickWrapper& _thick, FileListModel& fl):fileList(fl), thick(_thick)
{
	Draw(thick);
}


cOptionBarView::~cOptionBarView()
{

}

void cOptionBarView::Draw(ThickWrapper thick) {
	std::string strLabDefault = "Default Path:";
	std::string strLabEditable = "Input Path:";
	std::string strLabButton = "Recursive:";
	//Create top painted part
	thick.DrawContainer({ 0,0 }, thick.GetWinWidth() * 4, BACKGROUND_BLUE | BACKGROUND_RED);
	//Using overload 1 for DrawContainer() create default label
	thick.DrawContainer(strLabDefault, strLabDefault.length(), { thick.GetWinWidth() - 69, 1 }, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_RED);
	//Create text box default path
	//thick.DrawContainer("Default", 4, { thick.GetWinWidth() - 55, 1 }, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	//Using overload 1 for DrawContainer() create editable label
	thick.DrawContainer(strLabEditable, strLabEditable.length(), { thick.GetWinWidth() - 69, 3 }, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_RED);
	//Create text box edtiable path
	thick.DrawContainer({ thick.GetWinWidth() - 55 , 3 }, 50, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	//Using overload 1 for DrawContainer() create isRecursive Button
	thick.DrawContainer(strLabButton, strLabButton.length(), { thick.GetWinWidth() - 15, 1 }, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_RED);
	//Create text box isRecursive Button X
	thick.DrawContainer(" ", 1, { thick.GetWinWidth() - 4, 1 }, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
}

void cOptionBarView::Update()
{
	COORD loc{ thick.GetWinWidth() - 55, 1 };
	std::vector<FileInfo>& data = fileList.data;
	thick.DrawContainer(data[0].root_, data[0].root_.length(), loc, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);

}
