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
		{
			closesocket(m_hSocket);
			m_hSocket = NULL;
		}
		WSACleanup();
	}

	sockaddr_in AbstractSocket::CreateSockAddr(unsigned short port, std::string const & ipAddr)
	{
		sockaddr_in addr = { 0 };
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = (ipAddr == "") ? htonl(INADDR_ANY) : inet_addr(ipAddr.c_str());
		return addr;
	}
}