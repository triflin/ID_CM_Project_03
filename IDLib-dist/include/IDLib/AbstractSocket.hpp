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

		sockaddr_in CreateSockAddr(unsigned short port, std::string const& ipAddr = "");

	private:
		WSADATA				m_wsaData;

	protected:
		static unsigned short const MAX_BUFFER_SIZE = 65507;
		SOCKET				m_hSocket;
	};
}

#endif // __ABSTRACTSOCKET_HPP__