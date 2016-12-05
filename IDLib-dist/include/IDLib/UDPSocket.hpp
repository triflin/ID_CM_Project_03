#ifndef __UDPSOCKET_HPP__
#define __UDPSOCKET_HPP__

#include "AbstractSocket.hpp"
#include <string>
#include <type_traits>

namespace IDSocket
{
	class UDPSocket final : private AbstractSocket
	{
	public:
		// Constructors
		UDPSocket();
		UDPSocket(unsigned short port, std::string const& ipAddr = "");
		virtual ~UDPSocket();

		// Accessors
		bool IsBound() const { return m_isBound; }

		// Send/Recieve methods
		template <typename T>
		void Send(T& item, std::string const& ipAddr, unsigned short port);

		void Send(std::string& item, std::string const& ipAddr, unsigned short port);

		template <typename T>
		void Recieve(T& item, std::string const& ipAddr, unsigned short port);

		void Recieve(std::string& item, std::string const& ipAddr, unsigned short port);

		// Bind/Close
		void Bind(unsigned short port, std::string const& ipAddr = "");
		void Close();

	private:
		bool	m_isBound;
	};

	// Template implementations

	template <typename T>
	void UDPSocket::Send(T& item, std::string const& ipAddr, unsigned short port)
	{
		static_assert(std::is_pod<T>::value, "Item must be a POD type.");

		if (m_hSocket == NULL)
			throw SocketError("Socket has been closed.");

		if (!m_isBound)
			throw SocketError("Socket not bound.");

		// Create the address to send to
		sockaddr_in sendToAddr = CreateSockAddr(port, ipAddr);

		// Send the item
		int res = sendto(m_hSocket, reinterpret_cast<const char*>(&item), sizeof(item), 0, reinterpret_cast<sockaddr*>(&sendToAddr), sizeof(sendToAddr));
		if (res == SOCKET_ERROR)
			throw SocketError("Error sending data.");
	}

	template <typename T>
	void UDPSocket::Recieve(T& item, std::string const& ipAddr, unsigned short port)
	{
		static_assert(std::is_pod<T>::value, "Item must be a POD type.");

		if (m_hSocket == NULL)
			throw SocketError("Socket has been closed.");

		if (!m_isBound)
			throw SocketError("Socket not bound.");

		// Create the address to revive from
		sockaddr_in recvFromAddr = CreateSockAddr(port, ipAddr);

		socklen_t cbRecvFromAddr = sizeof(recvFromAddr);
		
		// Recieve the item
		int res = recvfrom(m_hSocket, reinterpret_cast<char*>(&item), sizeof(item), 0, reinterpret_cast<sockaddr*>(&recvFromAddr), &cbRecvFromAddr);
		if (res == SOCKET_ERROR)
			throw SocketError("Error recieving data.");
	}
}

#endif // __UDPSOCKET_HPP__