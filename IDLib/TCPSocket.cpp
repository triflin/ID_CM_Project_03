#include "TCPSocket.hpp"
#include "SocketError.hpp"

namespace IDSocket
{
	TCPSocket::TCPSocket(std::string const& ipAddr, unsigned short port)
	{
		m_hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	// STREAM+PROTO_TCP => TCP/IP

		// Set up the server address
		sockaddr_in listenerAddress = { 0 };
		listenerAddress.sin_family = AF_INET;
		listenerAddress.sin_port = htons(port);
		listenerAddress.sin_addr.s_addr = inet_addr(ipAddr.c_str());

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
}