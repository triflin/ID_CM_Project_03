#include "ThinWrapper.h"
bool ThinWrapper::finish = false;

BOOL CtrlHandler(DWORD ctrlType) {
	switch (ctrlType) {
	case CTRL_C_EVENT:
		ThinWrapper::finish = true;
		return TRUE;
	}
	return FALSE;
}

ThinWrapper::ThinWrapper()
{
	hConOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	hConInput = GetStdHandle(STD_INPUT_HANDLE);
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
}

ThinWrapper::~ThinWrapper()
{

}

BOOL ThinWrapper::getConsoleScreenBufferInfo(CONSOLE_SCREEN_BUFFER_INFO &origCSBI)
{
	return GetConsoleScreenBufferInfo(hConOutput, &origCSBI);
}

BOOL ThinWrapper::fillConsoleOutputCharacterA(CHAR x, DWORD consoleSize, COORD cursorHomeCoord, LPDWORD charsWritten)
{
	return FillConsoleOutputCharacterA(hConOutput, x, consoleSize, cursorHomeCoord, charsWritten);
}

BOOL ThinWrapper::fillConsoleOutputAttribute(WORD str, DWORD consoleSize, COORD cursorHomeCoord, LPDWORD charsWritten)
{
	return FillConsoleOutputAttribute(hConOutput, str, consoleSize, cursorHomeCoord, charsWritten);
}

BOOL ThinWrapper::writeConsoleOutputCharacterA(std::string const& msg, DWORD msgSize, COORD loc, LPDWORD nChars)
{
	return WriteConsoleOutputCharacterA(hConOutput, msg.c_str(), msgSize, loc, nChars);
}

BOOL ThinWrapper::readConsoleOutputA(PCHAR_INFO  origBuffer, COORD origCSBI, COORD origBuffCoord, SMALL_RECT buffRect)
{
	return ReadConsoleOutputA(hConOutput, origBuffer, origCSBI, origBuffCoord, &buffRect);
}

BOOL ThinWrapper::getConsoleCursorInfo(CONSOLE_CURSOR_INFO &origCCI)
{
	return GetConsoleCursorInfo(hConOutput, &origCCI);
}

BOOL ThinWrapper::setConsoleWindowInfo(BOOL x, SMALL_RECT smRect)
{
	return SetConsoleWindowInfo(hConOutput, x, &smRect);
}

BOOL ThinWrapper::setConsoleScreenBufferSize(COORD buffSize)
{
	return SetConsoleScreenBufferSize(hConOutput, buffSize);
}

BOOL ThinWrapper::setConsoleCursorInfo(CONSOLE_CURSOR_INFO &newCCI)
{
	return SetConsoleCursorInfo(hConOutput, &newCCI);
}

BOOL ThinWrapper::writeConsoleOutputA(PCHAR_INFO origBuff, COORD origCSBI, COORD origBuffCoord, SMALL_RECT originalCSBI)
{
	return WriteConsoleOutputA(hConOutput, origBuff, origCSBI, origBuffCoord, &originalCSBI);
}

BOOL ThinWrapper::writeConsoleOutputAttribute(WORD str, DWORD loc, COORD msg, LPDWORD nCharsWritten)
{
	return WriteConsoleOutputAttribute(hConOutput, &str, loc, msg, nCharsWritten);
}

BOOL ThinWrapper::setConsoleCursorPosition(CONSOLE_SCREEN_BUFFER_INFO origCSBI)
{
	return SetConsoleCursorPosition(hConOutput, origCSBI.dwCursorPosition);
}

BOOL ThinWrapper::setConsoleCtrlHandler(BOOL x)
{
	return SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, x);
}

BOOL ThinWrapper::setConsoleTitleA(LPCSTR str)
{
	return SetConsoleTitleA(str);
}

BOOL ThinWrapper::getConsoleMode(LPDWORD str)
{
	return GetConsoleMode(hStdin, str);
}

BOOL ThinWrapper::setConsoleMode(DWORD str)
{
	return SetConsoleMode(hStdin, str);
}

BOOL ThinWrapper::readConsoleInput(PINPUT_RECORD inBuffData, DWORD inBuffSize, LPDWORD numEvent)
{
	return ReadConsoleInput(hStdin, inBuffData, inBuffSize, numEvent);
}

BOOL ThinWrapper::isFinished()
{
	return finish;
}
