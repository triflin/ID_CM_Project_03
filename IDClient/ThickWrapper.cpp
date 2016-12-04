#include "ThickWrapper.h"
#include "XError.h"
#undef min

ThickWrapper::ThickWrapper() 
{

}


ThickWrapper::~ThickWrapper()
{

}


void ThickWrapper::SaveConsoleState() {
	THROW_IF_CONSOLE_ERROR(thin.getConsoleScreenBufferInfo(originalCSBI));

	// save the desktop
	originalBuffer.resize(originalCSBI.dwSize.X*originalCSBI.dwSize.Y);
	originalBufferCoord = COORD{ 0 };

	bufferRect.Bottom = originalCSBI.dwSize.Y - 1;
	bufferRect.Right = originalCSBI.dwSize.Y - 1;
	THROW_IF_CONSOLE_ERROR(thin.readConsoleOutputA(originalBuffer.data(), originalCSBI.dwSize, originalBufferCoord, bufferRect));

	// Save the cursorsb
	THROW_IF_CONSOLE_ERROR(thin.getConsoleCursorInfo(originalCCI));
}

void ThickWrapper::ResizeConsoleWindow() {

	THROW_IF_CONSOLE_ERROR(thin.setConsoleWindowInfo(TRUE, sr));

	COORD bufferSize;
	bufferSize.X = WINDOW_WIDTH;
	bufferSize.Y = WINDOW_HEIGHT;
	THROW_IF_CONSOLE_ERROR(thin.setConsoleScreenBufferSize(bufferSize));

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	THROW_IF_CONSOLE_ERROR(thin.getConsoleScreenBufferInfo(csbi));
	sr.Top = sr.Left = 0;
	WINDOW_WIDTH = std::min((SHORT)WINDOW_WIDTH, csbi.dwMaximumWindowSize.X);
	WINDOW_HEIGHT = std::min((SHORT)WINDOW_HEIGHT, csbi.dwMaximumWindowSize.Y);
	sr.Right = WINDOW_WIDTH - 1;
	sr.Bottom = WINDOW_HEIGHT - 1;

	THROW_IF_CONSOLE_ERROR(thin.setConsoleWindowInfo(TRUE, sr));
	currentConsoleWidth = sr.Right - sr.Left + 1;

	THROW_IF_CONSOLE_ERROR(thin.getConsoleCursorInfo(originalCCI));
	auto newCCI = originalCCI;
	newCCI.bVisible = FALSE;
	THROW_IF_CONSOLE_ERROR(thin.setConsoleCursorInfo(newCCI));
}

void ThickWrapper::RestoreConsoleState() {
	// restore the original window/buffer
	sr = SMALL_RECT{ 0 };
	THROW_IF_CONSOLE_ERROR(thin.setConsoleWindowInfo(TRUE, sr));
	THROW_IF_CONSOLE_ERROR(thin.setConsoleScreenBufferSize(originalCSBI.dwSize));
	THROW_IF_CONSOLE_ERROR(thin.setConsoleWindowInfo(TRUE, originalCSBI.srWindow));

	// Restore the desktop contents
	bufferRect = SMALL_RECT{ 0 };
	bufferRect.Bottom = originalCSBI.dwSize.Y - 1;
	bufferRect.Right = originalCSBI.dwSize.X - 1;
	THROW_IF_CONSOLE_ERROR(thin.writeConsoleOutputA(originalBuffer.data(), originalCSBI.dwSize, originalBufferCoord, originalCSBI.srWindow));


	// Restore the cursor
	THROW_IF_CONSOLE_ERROR(thin.setConsoleCursorInfo(originalCCI));
	THROW_IF_CONSOLE_ERROR(thin.setConsoleCursorPosition(originalCSBI));
}

void ThickWrapper::RightClickChange() {
	currColor++;
	if (currColor >= BGCOLORS.size()) {
		currColor = 1;
	}
}

void ThickWrapper::Clear() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	THROW_IF_CONSOLE_ERROR(thin.getConsoleScreenBufferInfo(csbi));

	// Fill the entire screen area
	DWORD charsWritten;
	DWORD consoleSize = csbi.dwSize.X*csbi.dwSize.Y;
	COORD cursorHomeCoord{ 0,0 };
	THROW_IF_CONSOLE_ERROR(thin.fillConsoleOutputCharacterA(' ', consoleSize, cursorHomeCoord, &charsWritten));
	THROW_IF_CONSOLE_ERROR(thin.fillConsoleOutputAttribute(BGCOLORS[0], consoleSize, cursorHomeCoord, &charsWritten));
}

SHORT ThickWrapper::GetWinWidth() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	THROW_IF_CONSOLE_ERROR(thin.getConsoleScreenBufferInfo(csbi));
	return csbi.dwSize.X;
}

SHORT ThickWrapper::GetWinHeight() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	THROW_IF_CONSOLE_ERROR(thin.getConsoleScreenBufferInfo(csbi));
	return csbi.dwSize.Y;
}

void ThickWrapper::ShowMessage(std::string const & msg, COORD location)
{
	DWORD nChars;
	thin.writeConsoleOutputCharacterA(msg, msg.size(), location, &nChars);
}

void ThickWrapper::DrawContainer(COORD start, DWORD size, WORD attr) {
	DWORD nCharsWritten;
	THROW_IF_CONSOLE_ERROR(thin.fillConsoleOutputCharacterA(' ', size, start, &nCharsWritten));
	THROW_IF_CONSOLE_ERROR(thin.fillConsoleOutputAttribute(attr, size, start, &nCharsWritten));
}

void ThickWrapper::DrawContainer(std::string msg, DWORD msgSize, COORD start, WORD attr) {
	DWORD nCharsWritten;
	THROW_IF_CONSOLE_ERROR(thin.writeConsoleOutputCharacterA(msg, msgSize, start, &nCharsWritten));
	THROW_IF_CONSOLE_ERROR(thin.fillConsoleOutputAttribute(attr, msgSize, start, &nCharsWritten));
}

BOOL ThickWrapper::setCtrlHandler(DWORD ctrlType)
{
	return thin.setConsoleCtrlHandler(TRUE);
}

BOOL ThickWrapper::isFinished()
{
	return thin.isFinished();
}
