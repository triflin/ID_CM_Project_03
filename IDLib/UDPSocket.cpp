#include "UDPSocket.hpp"
#include "SocketError.hpp"

#include <sstream>
#include <numeric>

#undef max

namespace IDSocket
{
	UDPSocket::UDPSocket() : m_isBound(false)
	{
		// Create the socket handle
		m_hSocket = socket(AF_INET, SOCK_DGRAM, 0);	// DATAGRAM => UDP/IP
	}

	UDPSocket::UDPSocket(unsigned short port, std::string const& ipAddr) : m_isBound(false)
	{
		// Create the socket handle
		m_hSocket = socket(AF_INET, SOCK_DGRAM, 0);	// DATAGRAM => UDP/IP
		Bind(port, ipAddr);
	}

	UDPSocket::~UDPSocket() {}

	void UDPSocket::Send(std::string& item, std::string const & ipAddr, unsigned short port)
	{
		if (m_hSocket == NULL)
			throw SocketError("Socket has been closed.");

		if (!m_isBound)
			throw SocketError("Socket not bound.");

		if (item.length() > static_cast<size_t>(std::numeric_limits<int>::max()))
		{
			std::ostringstream oss;
			oss << "String must have a maximum length of " << std::numeric_limits<int>::max() << "\n";
			throw SocketError(oss.str());
		}

		// Create the address to send to
		sockaddr_in sendToAddr = CreateSockAddr(port, ipAddr);

		int res = sendto(m_hSocket, item.c_str(), static_cast<int>(item.length()), 0, reinterpret_cast<sockaddr*>(&sendToAddr), sizeof(sendToAddr));
		if (res == SOCKET_ERROR)
			throw SocketError("Error sending data.");
	}

	void UDPSocket::Recieve(std::string& item, std::string const & ipAddr, unsigned short port)
	{
		if (m_hSocket == NULL)
			throw SocketError("Socket has been closed.");

		if (!m_isBound)
			throw SocketError("Socket not bound.");

		// Create the address to recieve from
		sockaddr_in recvFromAddr = CreateSockAddr(port, ipAddr);

		socklen_t cbRecvFromAddr = sizeof(recvFromAddr);

		char buffer[MAX_BUFFER_SIZE];
		int res = recvfrom(m_hSocket, buffer, MAX_BUFFER_SIZE, 0, reinterpret_cast<sockaddr*>(&recvFromAddr), &cbRecvFromAddr);
		if (res == SOCKET_ERROR)
			throw SocketError("Error recieving data");

		// Set the null terminator
		buffer[min(res, MAX_BUFFER_SIZE - 1)] = NULL;
		item = buffer;
	}

	void UDPSocket::Bind(unsigned short port, std::string const& ipAddr)
	{
		if (m_hSocket == NULL)
			throw SocketError("Socket has been closed.");

		if (m_isBound)
			throw SocketError("Socket already bound.");

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

	void UDPSocket::Close()
	{
		if (m_hSocket == NULL)
			throw SocketError("Socket already closed.");
		m_isBound = false;
		closesocket(m_hSocket);
		m_hSocket = NULL;
	}
}