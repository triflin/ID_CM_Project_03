#ifndef __UDPSOCKET_HPP__
#define __UDPSOCKET_HPP__

#include "AbstractSocket.hpp"
#include <string>

namespace IDSocket
{
	class UDPSocket : public AbstractSocket
	{
	public:
		UDPSocket();
		virtual ~UDPSocket();

		template <typename T>
		void Send(T* item, std::string const ipAddr, unsigned short port);

		template <typename T>
		void Recieve(T* item, std::string const ipAddr, unsigned short port);

		void Bind(unsigned short port, std::string const& ipAddr = "");

	private:
		static unsigned short const MAX_DATAGRAM_SIZE;
	};

	// Template implementations
	template <typename T>
	void UDPSocket::Send(T* item, std::string const ipAddr, unsigned short port)
	{
		// Create the address to send to
		sockaddr_in serverAddress = { 0 };
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_port = htons(port);
		serverAddress.sin_addr.s_addr = inet_addr(ipAddr.c_str());

		// Send the item
		int res = sendto(m_hSocket, (char*)item, sizeof(item), 0, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress));
		if (res == SOCKET_ERROR)
			throw SocketError();
	}

	template <typename T>
	void UDPSocket::Recieve(T* item, std::string const ipAddr, unsigned short port)
	{
		// Create the client address to revive from
		sockaddr_in clientAddress = { 0 };
		clientAddress.sin_family = AF_INET;
		clientAddress.sin_port = htons(port);
		clientAddress.sin_addr.s_addr = inet_addr(ipAddr.c_str());

		socklen_t cbClientaddress = sizeof(clientAddress);

		// Recieve the item
		int res = recvfrom(m_hSocket, (char*)item, MAX_DATAGRAM_SIZE, 0, reinterpret_cast<sockaddr*>(&clientAddress), &cbClientaddress);
		if (res == SOCKET_ERROR)
			throw SocketError();
	}
}

#endif // __UDPSOCKET_HPP__