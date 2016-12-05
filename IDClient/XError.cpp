#include "XError.h"

XError::~XError()
{
}

XError::string_type XError::msg()
{
	std::ostringstream oss;
	oss << "Error: " << code() << "\n";
	oss << ErrorDescription(code()) << "\n";
	oss << "In: " << file() << "\n";
	oss << "Line: " << line() << "\n";
	return oss.str();
}

#pragma region XError

std::string XError::ErrorDescription(DWORD dwMessageID) {
	char* msg;
	auto c = FormatMessageA(
		/* flags */			FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS |
		FORMAT_MESSAGE_MAX_WIDTH_MASK,
		/* source */		NULL,
		/* message ID */	dwMessageID,
		/* language */		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		/* buffer */		(LPSTR)&msg,
		/* size */			0,
		/* args */			NULL
		);
	std::string strMsg = (c == 0) ? "unknown" : msg;
	LocalFree(msg);
	return strMsg;
}

#pragma endregion // XError