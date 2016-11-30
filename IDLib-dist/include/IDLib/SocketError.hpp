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
		const char* what() const override;

		int GetErrorCode() const { return m_errno; }

	private:
		std::string m_msg;
		int m_errno;
	};
}

#endif