#include "cFileView.h"
#include "XError.h"

cFileView::cFileView(ThickWrapper thick)
{
	Draw(thick);
}


cFileView::~cFileView()
{

}

void cFileView::Draw(ThickWrapper thick) {
	LPCSTR strLabFoldCount = "Folder Count:";
	LPCSTR strLabFileCount = "File Count:";
	LPCSTR strTotSize = "Total Size:";

	//Create bottom painted part
	thick.DrawContainer({ 0,thick.GetWinHeight() - 3 }, thick.GetWinWidth() * 3, BACKGROUND_BLUE);
	//Using overload 1 for DrawContainer() create FoldersCount label
	thick.DrawContainer(strLabFoldCount, strlen(strLabFoldCount), { 1 ,thick.GetWinHeight() - 2 }, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
	//Create text box FoldersCount
	thick.DrawContainer({ 15 ,thick.GetWinHeight() - 2 }, 5, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	//Using overload 1 for DrawContainer() create strLabFileCount label
	thick.DrawContainer(strLabFileCount, strlen(strLabFileCount), { 25 ,thick.GetWinHeight() - 2 }, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
	//Create text box strLabFileCount
	thick.DrawContainer({ 37 ,thick.GetWinHeight() - 2 }, 5, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	//Using overload 1 for DrawContainer() create strTotSize label
	thick.DrawContainer(strTotSize, strlen(strTotSize), { 50 ,thick.GetWinHeight() - 2 }, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
	//Create text box strTotSize
	thick.DrawContainer({ 62 ,thick.GetWinHeight() - 2 }, 5, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
}

void cFileView::Update()
{

}