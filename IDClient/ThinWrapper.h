#pragma once
#include <Windows.h>
#include <string>
#include <algorithm>

class ThinWrapper
{
private:
	HANDLE hConOutput, hConInput, hStdin;

public:
	ThinWrapper();
	~ThinWrapper();

	static bool finish;

	BOOL getConsoleScreenBufferInfo(CONSOLE_SCREEN_BUFFER_INFO & origCSBI);

	BOOL fillConsoleOutputCharacterA(CHAR x, DWORD consoleSize, COORD cursorHomeCoord, LPDWORD charsWritten);

	BOOL fillConsoleOutputAttribute(WORD str, DWORD consoleSize, COORD cursorHomeCoord, LPDWORD charsWritten);

	BOOL readConsoleOutputA(PCHAR_INFO origBuffer, COORD origCSBI, COORD origBuffCoord, SMALL_RECT buffRect);

	BOOL getConsoleCursorInfo(CONSOLE_CURSOR_INFO & origCCI);

	BOOL setConsoleWindowInfo(BOOL x, SMALL_RECT smRect);

	BOOL setConsoleScreenBufferSize(COORD buffSize);

	BOOL setConsoleCursorInfo(CONSOLE_CURSOR_INFO & newCCI);

	BOOL writeConsoleOutputA(PCHAR_INFO origBuff, COORD origCSBI, COORD origBuffCoord, SMALL_RECT originalCSBI);

	BOOL writeConsoleOutputAttribute(WORD str, DWORD loc, COORD msg, LPDWORD nCharsWritten);

	BOOL setConsoleCursorPosition(CONSOLE_SCREEN_BUFFER_INFO origCSBI);

	BOOL setConsoleCtrlHandler(BOOL x);

	BOOL setConsoleTitleA(LPCSTR x);

	BOOL getConsoleMode(LPDWORD str);

	BOOL setConsoleMode(DWORD str);

	BOOL writeConsoleOutputCharacterA(std::string const& msg, DWORD msgSize, COORD loc, LPDWORD nChars);

	BOOL readConsoleInput(PINPUT_RECORD inBuffData, DWORD inBuffSize, LPDWORD numEvent);

	BOOL isFinished();

};

