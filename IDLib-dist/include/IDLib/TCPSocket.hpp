#ifndef __TCPSOCKET_HPP__
#define __TCPSOCKET_HPP__

#include "AbstractSocket.hpp"
#include <string>
#include <type_traits>

namespace IDSocket
{
	class TCPSocket : public AbstractSocket
	{
	public:
		TCPSocket(std::string const& ipAddr, unsigned short port);
		virtual ~TCPSocket();

		template <typename T>
		void Send(T& item);

		void Send(std::string& item);

		template <typename T>
		void Recieve(T& item);

		void Recieve(std::string& item);
	};

	// Template implementations

	template <typename T>
	void TCPSocket::Send(T& item)
	{
		static_assert(std::is_pod<T>::value, "Item must be a POD type.");

		int res = send(m_hSocket, reinterpret_cast<const char*>(&item), sizeof(item), 0);
		if (res == SOCKET_ERROR)
			throw SocketError();
	}

	template <typename T>
	void TCPSocket::Recieve(T& item)
	{
		static_assert(std::is_pod<T>::value, "Item must be a POD type.");

		int res = recv(m_hSocket, reinterpret_cast<char*>(&item), sizeof(item), 0);
		if (res == SOCKET_ERROR)
			throw SocketError();
	}
}

#endif