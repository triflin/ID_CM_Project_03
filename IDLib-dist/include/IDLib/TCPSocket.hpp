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

		template <typename T>
		void Recieve(T& item);
	};

	// Template implementations

	template <typename T>
	void TCPSocket::Send(T& item)
	{
		
	}

	template <typename T>
	void TCPSocket::Recieve(T& item)
	{

	}
}

#endif