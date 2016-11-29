#ifndef __SOCKETERROR_HPP__
#define __SOCKETERROR_HPP__

#include <string>

namespace IDSocket
{
	class SocketError : std::exception
	{
	public:
		SocketError();
		SocketError(std::string const& msg);
		const char* what() const;

	private:
		std::string m_msg;
	};
}

#endif