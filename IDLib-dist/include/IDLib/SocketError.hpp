#ifndef __SOCKETERROR_HPP__
#define __SOCKETERROR_HPP__

#include <string>

namespace IDSocket
{
	class SocketError
	{
	public:
		SocketError();
		SocketError(std::wstring const& msg);
		std::wstring GetErrorMessage() const;

	private:
		std::wstring	m_msg;
	};
}

#endif