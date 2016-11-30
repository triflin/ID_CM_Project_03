#include "TCPSocket.hpp"
#include "SocketError.hpp"

namespace IDSocket
{
	// Contructors
	TCPSocket::TCPSocket() : m_isConnected(false)
	{
		m_hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	// STREAM+PROTO_TCP => TCP/IP
	}

	TCPSocket::TCPSocket(std::string const& ipAddr, unsigned short port) : m_isConnected(false)
	{
		m_hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	// STREAM+PROTO_TCP => TCP/IP
		Connect(ipAddr, port);
	}

	TCPSocket::~TCPSocket()
	{
		if (m_hSocket != NULL)
			Disconnect();
	}

	// Friend constructor
	TCPSocket::TCPSocket(SOCKET handle)
	{
		m_hSocket = handle;
		m_isConnected = m_hSocket != NULL;
	}

	// Send/Recieve
	void TCPSocket::Send(std::string& item)
	{
		if (m_hSocket == NULL)
			throw SocketError("Socket has been closed.");

		if (!m_isConnected)
			throw SocketError("Socket not connected.");

		int res = send(m_hSocket, item.c_str(), static_cast<int>(item.length()), 0);
		if (res == SOCKET_ERROR)
			throw SocketError();
	}

	void TCPSocket::Recieve(std::string& item)
	{
		if (m_hSocket == NULL)
			throw SocketError("Socket has been closed.");

		if (!m_isConnected)
			throw SocketError("Socket not connected.");

		char buffer[MAX_BUFFER_SIZE];
		int res = recv(m_hSocket, buffer, MAX_BUFFER_SIZE, 0);
		if (res == SOCKET_ERROR)
			throw SocketError();
		
		buffer[min(res, MAX_BUFFER_SIZE - 1)] = NULL;
		item = buffer;
	}

	// Connect/Disconnect
	void TCPSocket::Connect(std::string const& ipAddr, unsigned short port)
	{
		if (m_hSocket == NULL)
			throw SocketError("Socket has been closed.");

		sockaddr_in addr = CreateSockAddr(port, ipAddr);

		int res = connect(m_hSocket, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
		if (res == SOCKET_ERROR)
			throw SocketError("Could not connect to the remote IP address.");

		m_isConnected = true;
	}

	void TCPSocket::Disconnect()
	{
		if (m_hSocket == NULL)
			throw SocketError("Socket has been closed.");

		if (!m_isConnected)
			throw SocketError("Socket is already disconnected.");

		m_isConnected = false;
		closesocket(m_hSocket);
		m_hSocket = NULL;
	}
}