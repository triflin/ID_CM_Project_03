#ifndef __TCPLISTENER_HPP__
#define __TCPLISTENER_HPP__

#include "TCPSocket.hpp"

#include <memory>

namespace IDSocket
{
	class TCPListener : public AbstractSocket
	{
	public:
		TCPListener();
		TCPListener(std::string const& ipAddr, unsigned short port);
		virtual ~TCPListener();

		// Accessors
		bool IsListening() const { return m_isListening; }

		void Listen(std::string const& ipAddr, unsigned short port);
		std::shared_ptr<TCPSocket> Accept();
		void Close();

	private:
		bool	m_isListening;
	};
}

#endif