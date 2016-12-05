#include <iostream>
#include <vector>
#include <Windows.h>
#include <sstream>
#include <algorithm>
#include <conio.h>
#include "XError.h"
#include "ThickWrapper.h"
#include "IView.h"
#include "Controller.h"
#include "RegexSearch.h"


int main(int argc, char* argv[]) try {

#if defined(_DEBUG) 
	int dbgFlags = ::_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	// bitwise or checks the block integrity on every memory call
	dbgFlags |= _CRTDBG_CHECK_ALWAYS_DF;
	//don't always remove blocks on delete
	dbgFlags |= _CRTDBG_DELAY_FREE_MEM_DF;
	//check for memory leaks at process terminatio
	dbgFlags |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(dbgFlags);
#endif

	SetConsoleTitleA("TUI Paint");
	ThickWrapper	thick;

	thick.SaveConsoleState();
	thick.ResizeConsoleWindow();

	Controller controller(thick, argc, argv);

	auto hStdin = GetStdHandle(STD_INPUT_HANDLE);

	// Install a control handler to trap ^C
	if (thick.setCtrlHandler(FALSE)) {

	}
	else {
		std::cerr << "ERROR: failed to install control handler." << std::endl;
		return EXIT_FAILURE;
	}

	// Configure the console mode
	DWORD oldConsoleMode;
	GetConsoleMode(hStdin, &oldConsoleMode);

	DWORD consoleMode = ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, consoleMode)) {
		std::cerr << "\nError: could not restore original console mode.\n";
		return EXIT_FAILURE;
	}

	// read input buffer repeatedly
	std::vector<INPUT_RECORD> inBuffer(128);
	while (!thick.isFinished()) {
		DWORD numEvent;
		if (!ReadConsoleInput(hStdin, inBuffer.data(), inBuffer.size(), &numEvent)) {
			std::cerr << "Failed to read console input\n";
			break;
		}

		for (size_t iEvent = 0; iEvent < numEvent; ++iEvent) {
			switch (inBuffer[iEvent].EventType) {
			case MOUSE_EVENT:
				thick.ProcessMouseEvent(inBuffer[iEvent].Event.MouseEvent);
				break;
			case KEY_EVENT:
				thick.ProcessKeyEvent(inBuffer[iEvent].Event.KeyEvent);
				break;
			}
		}
	}
	thick.RestoreConsoleState();
	std::cout << "Ctrl-C pressed" << std::endl;
	//_getch();
	std::cout << "Finished" << std::endl;
	if (!SetConsoleMode(hStdin, oldConsoleMode)) {
		std::cerr << "\nError: could not restore original console mode.\n";
		return EXIT_FAILURE;
	}

}
catch (XError& e) {
	MessageBoxA(NULL, e.msg().c_str(), "Runtime Error", MB_OK);
}

void UpdateAll() {

}

//Paint screen using mouse event
//void ThickWrapper::PaintScreen(MOUSE_EVENT_RECORD const & mer)
//{
//	CONSOLE_SCREEN_BUFFER_INFO csbi;
//	thin.getConsoleScreenBufferInfo(csbi);
//
//	// Fill the entire screen area
//	DWORD charsWritten;
//	DWORD consoleSize = csbi.dwSize.X*csbi.dwSize.Y;
//	COORD cursorHomeCoord{ 0,0 };
//
//	if (!isStarted) {
//		THROW_IF_CONSOLE_ERROR(thin.fillConsoleOutputCharacterA(' ', consoleSize, cursorHomeCoord, &charsWritten));
//	}
//
//	if (!isStarted) {
//		THROW_IF_CONSOLE_ERROR(thin.fillConsoleOutputAttribute(BGCOLORS[0], consoleSize, cursorHomeCoord, &charsWritten));
//		isStarted = true;
//	}
//
//	std::string msg = " ";
//	COORD loc;
//	loc.X = mer.dwMousePosition.X;
//	loc.Y = mer.dwMousePosition.Y;
//	DWORD nCharsWritten;
//	THROW_IF_CONSOLE_ERROR(thin.writeConsoleOutputCharacterA(msg.c_str(), (DWORD)msg.size(), loc, &nCharsWritten));
//	THROW_IF_CONSOLE_ERROR(thin.writeConsoleOutputAttribute(BGCOLORS[currColor], msg.size(), loc, &nCharsWritten));
//}



void ThickWrapper::ProcessMouseEvent(MOUSE_EVENT_RECORD const& mer) {

	auto mask = mer.dwButtonState;
	switch (mer.dwEventFlags) {
	case 0: // button pressed or released
	{
		if (mask&FROM_LEFT_1ST_BUTTON_PRESSED)
			//PaintScreen(mer);
		if (mask&RIGHTMOST_BUTTON_PRESSED)
			RightClickChange();
		if (!mask) {};
	}
	break;
	case MOUSE_MOVED:
		if (mask&FROM_LEFT_1ST_BUTTON_PRESSED)
			//PaintScreen(mer);
		break;

	default:
		break;
	}
	auto bufferLoc = mer.dwMousePosition;
}

void ThickWrapper::ProcessKeyEvent(KEY_EVENT_RECORD const& ker) {
	auto ks = ker.dwControlKeyState;
	if (!ker.bKeyDown && (ker.uChar.AsciiChar == 'c' || 'C'))
		Clear();
}