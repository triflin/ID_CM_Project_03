#include "AbstractSocket.hpp"

#include <stdexcept>
#include <iostream>
#include "SocketError.hpp"

namespace IDSocket
{
	AbstractSocket::AbstractSocket() :
		m_hSocket(NULL)
	{
		int startupResult = WSAStartup(MAKEWORD(2, 2), &m_wsaData);
		if (startupResult != 0)
			throw SocketError();

		// Subclasses create the socket handle...
	}

	AbstractSocket::~AbstractSocket()
	{
		if (m_hSocket != NULL)
			closesocket(m_hSocket);
		WSACleanup();
	}
}