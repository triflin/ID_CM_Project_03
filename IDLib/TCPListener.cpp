#include "TCPListener.hpp"
#include "SocketError.hpp"

namespace IDSocket
{
	TCPListener::TCPListener() : m_isListening(false)
	{
		m_hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	// STREAM+PROTO_TCP => TCP/IP
	}

	TCPListener::TCPListener(std::string const& ipAddr, unsigned short port) : m_isListening(false)
	{
		m_hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	// STREAM+PROTO_TCP => TCP/IP
		Listen(ipAddr, port);
	}

	TCPListener::~TCPListener() {}

	void TCPListener::Listen(std::string const& ipAddr, unsigned short port)
	{
		if (m_hSocket == NULL)
			throw SocketError("Socket has been closed.");

		if (m_isListening)
			throw SocketError("Socket already listening.");

		sockaddr_in addr = CreateSockAddr(port, ipAddr);

		// Bind to the local IP
		int res = bind(m_hSocket, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
		if (res == SOCKET_ERROR)
			throw SocketError("Error binding the socket.");

		// Start listening
		res = listen(m_hSocket, 1);
		if (res == SOCKET_ERROR)
			throw SocketError("Error on listen.");

		m_isListening = true;
	}

	TCPSocket TCPListener::Accept()
	{
		if (m_hSocket == NULL)
			throw SocketError("Socket has been closed.");

		if (!m_isListening)
			throw SocketError("Socket is not in listening state.");

		// Get the connection
		SOCKET s = SOCKET_ERROR;
		while (s == SOCKET_ERROR)
			s = accept(m_hSocket, NULL, NULL);

		return TCPSocket(s);
	}

	void TCPListener::Close()
	{
		if (m_hSocket == NULL)
			throw SocketError("Socket already closed.");
		m_isListening = false;
		closesocket(m_hSocket);
		m_hSocket = NULL;
	}
}