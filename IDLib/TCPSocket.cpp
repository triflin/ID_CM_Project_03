#include "TCPSocket.hpp"

namespace IDSocket
{
	TCPSocket::TCPSocket()
	{
		m_hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	// STREAM+PROTO_TCP => TCP/IP
	}

	TCPSocket::~TCPSocket()
	{
	}
}