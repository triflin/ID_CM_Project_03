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

	protected:
		WSADATA				m_wsaData;
		SOCKET				m_hSocket;
	};
}

#endif // __ABSTRACTSOCKET_HPP__