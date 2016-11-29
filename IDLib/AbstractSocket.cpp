#include "AbstractSocket.hpp"

#include <stdexcept>
#include <iostream>
#include "SocketError.hpp"

namespace IDSocket
{
	AbstractSocket::AbstractSocket() :
		m_hSocket(NULL),
		m_isBound(false)
	{
		int startupResult = WSAStartup(MAKEWORD(2, 2), &m_wsaData);
		if (startupResult != 0)
			throw SocketError();

		// Subclasses create the socket handle...
	}

	AbstractSocket::~AbstractSocket()
	{
		if (m_hSocket != NULL)
			Close();
		WSACleanup();
	}

	void AbstractSocket::Close()
	{
		closesocket(m_hSocket);
		m_hSocket = NULL;
	}

	sockaddr_in AbstractSocket::CreateSockAddr(unsigned short port, std::string const & ipAddr)
	{
		sockaddr_in addr = { 0 };
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = (ipAddr == "") ? htonl(INADDR_ANY) : inet_addr(ipAddr.c_str());
		return addr;
	}

	void AbstractSocket::Bind(unsigned short port, std::string const& ipAddr)
	{
		if (m_isBound)
		{
			throw SocketError("Socket already bound.");
		}

		// Set up the server address
		sockaddr_in serverAddress = CreateSockAddr(port, ipAddr);

		// Bind to the server address
		int res = bind(m_hSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(sockaddr_in));
		if (res == SOCKET_ERROR)
		{
			throw SocketError("Error binding the socket.");
		}
		else
		{
			m_isBound = true;
		}
	}
}