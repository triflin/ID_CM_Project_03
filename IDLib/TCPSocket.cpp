#include "TCPSocket.hpp"
#include "SocketError.hpp"

namespace IDSocket
{
	TCPSocket::TCPSocket(std::string const& ipAddr, unsigned short port)
	{
		m_hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	// STREAM+PROTO_TCP => TCP/IP

		// Set up the server address
		sockaddr_in listenerAddress = CreateSockAddr(port, ipAddr);

		// Bind to the server address
		int res = connect(m_hSocket, reinterpret_cast<sockaddr*>(&listenerAddress), sizeof(listenerAddress));
		if (res == SOCKET_ERROR)
		{
			throw SocketError();
		}
	}

	TCPSocket::~TCPSocket()
	{
	}

	void TCPSocket::Send(std::string& item)
	{
		int res = send(m_hSocket, item.c_str(), static_cast<int>(item.length()), 0);
		if (res == SOCKET_ERROR)
			throw SocketError();
	}

	void TCPSocket::Recieve(std::string& item)
	{
		char buffer[MAX_BUFFER_SIZE];
		int res = recv(m_hSocket, buffer, MAX_BUFFER_SIZE, 0);
		if (res == SOCKET_ERROR)
			throw SocketError();
		
		buffer[min(res, MAX_BUFFER_SIZE - 1)] = NULL;
		item = buffer;
	}
}