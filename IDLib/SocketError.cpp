#include "SocketError.hpp"
#include "AbstractSocket.hpp"

namespace IDSocket
{
	std::wstring SocketError::GetErrorMessage() const
	{
		int err = WSAGetLastError();
		
		wchar_t* msg;
		auto c = FormatMessageW(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS |
			FORMAT_MESSAGE_MAX_WIDTH_MASK,
			NULL,
			err,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPWSTR)&msg,
			0,
			NULL
		);

		std::wstring strMsg = (c == 0) ? L"unknown" : msg;
		LocalFree(msg);
		return strMsg;
	}
}
