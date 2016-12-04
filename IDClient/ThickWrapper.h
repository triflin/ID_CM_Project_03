#pragma once
#include "ThinWrapper.h"
#include "IView.h"
#include <vector>

class ThickWrapper
{
private:
	//SystemData
	int currColor = 1;
	bool isStarted = false;
	ThinWrapper					thin;

	CONSOLE_SCREEN_BUFFER_INFO	originalCSBI;
	CONSOLE_CURSOR_INFO			originalCCI;
	std::vector<CHAR_INFO>		originalBuffer;
	COORD						originalBufferCoord;
	DWORD						originalConsoleMode;
	WORD						currentConsoleWidth;
	std::vector<WORD>BGCOLORS{
		0,
		BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
		BACKGROUND_RED,
		BACKGROUND_GREEN,
		BACKGROUND_BLUE
	};

	WORD WINDOW_HEIGHT = 50;
	WORD WINDOW_WIDTH = 70;
	SMALL_RECT bufferRect{ 0 };
	SMALL_RECT sr{ 0 };


public:
	ThickWrapper();
	~ThickWrapper();

	void SaveConsoleState();
	void ResizeConsoleWindow();
	void PaintScreen(MOUSE_EVENT_RECORD const& mer);
	void RestoreConsoleState();
	void RightClickChange();
	void Clear();
	void ProcessMouseEvent(MOUSE_EVENT_RECORD const& mer);
	void ProcessKeyEvent(KEY_EVENT_RECORD const& ker);
	BOOL setCtrlHandler(DWORD ctrlType);
	BOOL isFinished();
	SHORT GetWinWidth();
	SHORT GetWinHeight();
	void ShowMessage(std::string const& msg, COORD location);
	void DrawContainer(COORD start, DWORD size, WORD attr);
	void DrawContainer(std::string msg, DWORD msgSize, COORD start, WORD attr);
};

