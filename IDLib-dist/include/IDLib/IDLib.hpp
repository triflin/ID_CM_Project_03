#ifndef __IDLIB_HPP__
#define __IDLIB_HPP__

#include "UDPSocket.hpp"
#include "TCPSocket.hpp"
#include "TCPListener.hpp"
#include "SocketError.hpp"

// Link against proper library
#ifdef _DEBUG
#pragma comment (lib, "IDLib-mt-gd.lib")
#else
#pragma comment (lib, "IDLib-mt.lib")
#endif

#endif // __IDLIB_HPP__