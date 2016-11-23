#ifndef __UDPSOCKET_HPP__
#define __UDPSOCKET_HPP__

#include "AbstractSocket.hpp"
#include <string>
#include <type_traits>

namespace IDSocket
{
	class UDPSocket : public AbstractSocket
	{
	public:
		UDPSocket();
		virtual ~UDPSocket();

		template <typename T>
		void Send(T& item, std::string const& ipAddr, unsigned short port);

		template <typename T>
		void Recieve(T& item, std::string const& ipAddr, unsigned short port);

		void Bind(unsigned short port, std::string const& ipAddr = "");

	private:
		static unsigned short const MAX_DATAGRAM_SIZE = 65507;
	};

	// Template implementations
#define TYPE_CHECK(T) static_assert(std::is_same<T, std::string>::value || std::is_pod<T>::value, "Value must be POD or std::string.")

	template <typename T>
	void UDPSocket::Send(T& item, std::string const& ipAddr, unsigned short port)
	{
		TYPE_CHECK(T);

		// Create the address to send to
		sockaddr_in sendToAddr = { 0 };
		sendToAddr.sin_family = AF_INET;
		sendToAddr.sin_port = htons(port);
		sendToAddr.sin_addr.s_addr = inet_addr(ipAddr.c_str());

		// Send the item
		int res = SOCKET_ERROR;
		if (std::is_same<T, std::string>::value)
		{
			res = sendto(m_hSocket, item.c_str(), item.length(), 0, reinterpret_cast<sockaddr*>(&sendToAddr), sizeof(sendToAddr));
		}
		else
		{
			res = sendto(m_hSocket, reinterpret_cast<const char*>(&item), sizeof(item), 0, reinterpret_cast<sockaddr*>(&sendToAddr), sizeof(sendToAddr));
		}
		if (res == SOCKET_ERROR)
			throw SocketError();
	}

	template <typename T>
	void UDPSocket::Recieve(T& item, std::string const& ipAddr, unsigned short port)
	{
		TYPE_CHECK(T);

		// Create the client address to revive from
		sockaddr_in recvFromAddr = { 0 };
		recvFromAddr.sin_family = AF_INET;
		recvFromAddr.sin_port = htons(port);
		recvFromAddr.sin_addr.s_addr = inet_addr(ipAddr.c_str());

		socklen_t cbRecvFromAddr = sizeof(recvFromAddr);
		
		// Recieve the item
		int res = SOCKET_ERROR;
		if (std::is_same<T, std::string>::value)
		{
			char buffer[MAX_DATAGRAM_SIZE];
			res = recvfrom(m_hSocket, buffer, MAX_DATAGRAM_SIZE, 0, reinterpret_cast<sockaddr*>(&recvFromAddr), &cbRecvFromAddr);
			buffer[min(res, MAX_DATAGRAM_SIZE - 1)] = NULL;		// set the null terminator
			item = buffer;
		}
		else
		{
			res = recvfrom(m_hSocket, reinterpret_cast<char*>(&item), MAX_DATAGRAM_SIZE, 0, reinterpret_cast<sockaddr*>(&recvFromAddr), &cbRecvFromAddr);
		}
		if (res == SOCKET_ERROR)
			throw SocketError();
	}
#undef TYPE_CHECK
}

#endif // __UDPSOCKET_HPP__