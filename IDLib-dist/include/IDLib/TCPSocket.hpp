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
		// Constructors
		TCPSocket();
		TCPSocket(std::string const& ipAddr, unsigned short port);
		virtual ~TCPSocket();

		// Accessors
		bool IsConnected() const { return m_isConnected; }

		// Send/Recieve methods
		template <typename T>
		void Send(T& item);

		void Send(std::string& item);

		template <typename T>
		void Recieve(T& item);

		void Recieve(std::string& item);

		// Connect/Disconnect
		void Connect(std::string const& ipAddr, unsigned short port);
		void Disconnect();

	private:
		bool	m_isConnected;

	private:
		TCPSocket(SOCKET handle);
		friend class TCPListener;
	};

	// Template implementations

	template <typename T>
	void TCPSocket::Send(T& item)
	{
		static_assert(std::is_pod<T>::value, "Item must be a POD type.");

		if (m_hSocket == NULL)
			throw SocketError("Socket has been closed.");

		if (!m_isConnected)
			throw SocketError("Socket not connected.");

		int res = send(m_hSocket, reinterpret_cast<const char*>(&item), sizeof(item), 0);
		if (res == 0)
		{
			// Socket has been closed
			m_isConnected = false;
			m_hSocket = NULL;
		}
		else if (res == SOCKET_ERROR)
			throw SocketError("Error sending data.");
	}

	template <typename T>
	void TCPSocket::Recieve(T& item)
	{
		static_assert(std::is_pod<T>::value, "Item must be a POD type.");

		if (m_hSocket == NULL)
			throw SocketError("Socket has been closed.");

		if (!m_isConnected)
			throw SocketError("Socket not connected.");

		int res = recv(m_hSocket, reinterpret_cast<char*>(&item), sizeof(item), 0);
		if (res == 0)
		{
			// Socket has been closed
			m_isConnected = false;
			m_hSocket = NULL;
		}
		else if (res == SOCKET_ERROR)
			throw SocketError("Error recieving data.");
	}
}

#endif