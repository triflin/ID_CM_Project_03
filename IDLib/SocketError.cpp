#include "SocketError.hpp"
#include "AbstractSocket.hpp"

namespace IDSocket
{
	SocketError::SocketError() : m_msg("Internal socket error.")
	{
		m_errno = WSAGetLastError();
	}

	SocketError::SocketError(std::string const& msg) : m_msg(msg)
	{
		m_errno = WSAGetLastError();
	}

	const char* SocketError::what() const
	{
		return m_msg.c_str();
	}
}
