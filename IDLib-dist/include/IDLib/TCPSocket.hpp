#ifndef __TCPSOCKET_HPP__
#define __TCPSOCKET_HPP__

#include "AbstractSocket.hpp"

namespace IDSocket
{
	class TCPSocket : public AbstractSocket
	{
	public:
		TCPSocket();
		virtual ~TCPSocket();

		template <typename T>
		void Send(T& item);

		template <typename T>
		void Recieve(T& item);
	};

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