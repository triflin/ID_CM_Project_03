#include "SocketError.hpp"
#include "AbstractSocket.hpp"

namespace IDSocket
{
	SocketError::SocketError() {}

	SocketError::SocketError(std::wstring const& msg) : m_msg(msg) {}

	std::wstring SocketError::GetErrorMessage() const
	{
		// If a custom error message was set. Return it.
		if (!m_msg.empty())
			return m_msg;

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
