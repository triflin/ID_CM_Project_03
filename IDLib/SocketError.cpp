#include "SocketError.hpp"
#include "AbstractSocket.hpp"

namespace IDSocket
{
	SocketError::SocketError() {}

	SocketError::SocketError(std::string const& msg) : m_msg(msg) {}

	const char* SocketError::what() const
	{
		// If a custom error message was set. Return it.
		if (!m_msg.empty())
			return m_msg.c_str();

		return "Internal socket error.";
	}
}
