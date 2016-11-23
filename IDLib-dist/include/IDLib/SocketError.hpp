#ifndef __SOCKETERROR_HPP__
#define __SOCKETERROR_HPP__

#include <string>

namespace IDSocket
{
	class SocketError
	{
	public:
		std::wstring GetErrorMessage() const;
	};
}

#endif