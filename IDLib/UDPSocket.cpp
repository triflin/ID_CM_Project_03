#include "UDPSocket.hpp"
#include "SocketError.hpp"

namespace IDSocket
{
	unsigned short const UDPSocket::MAX_DATAGRAM_SIZE = 256;

	UDPSocket::UDPSocket()
	{
		m_hSocket = socket(AF_INET, SOCK_DGRAM, 0);	// DATAGRAM => UDP/IP
	}

	UDPSocket::~UDPSocket() {}

	void UDPSocket::Bind(unsigned short port, std::string const& ipAddr)
	{
		// Set up the server address
		sockaddr_in serverAddress = { 0 };
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_port = htons(port);
		serverAddress.sin_addr.s_addr = (ipAddr == "") ? htonl(INADDR_ANY) : inet_addr(ipAddr.c_str());

		// Bind to the server address
		int res = bind(m_hSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(sockaddr_in));
		if (res == SOCKET_ERROR)
		{
			throw SocketError();
		}
	}
}