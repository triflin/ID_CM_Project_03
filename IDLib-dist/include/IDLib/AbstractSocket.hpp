#ifndef __ABSTRACTSOCKET_HPP__
#define __ABSTRACTSOCKET_HPP__

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include <string>

namespace IDSocket
{
	class AbstractSocket
	{
	protected:
		AbstractSocket();
		virtual ~AbstractSocket();

		bool IsBound() const { return m_isBound; }

		sockaddr_in CreateSockAddr(unsigned short port, std::string const& ipAddr = "");

	public:
		void Bind(unsigned short port, std::string const& ipAddr = "");
		void Close();

	private:
		WSADATA				m_wsaData;
		bool				m_isBound;

	protected:
		static unsigned short const MAX_BUFFER_SIZE = 65507;
		SOCKET				m_hSocket;
	};
}

#endif // __ABSTRACTSOCKET_HPP__