#include <iostream>
using namespace std;

#include <IDLib\IDLib.hpp>
using namespace IDSocket;

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <Windows.h>
#include <crtdbg.h>
#endif

int main() {
#if defined(_DEBUG)
	int dbgFlags = ::_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	// bitwise or checks the block integrity on every memory call
	dbgFlags |= _CRTDBG_CHECK_ALWAYS_DF;
	//don't always remove blocks on delete
	dbgFlags |= _CRTDBG_DELAY_FREE_MEM_DF;
	//check for memory leaks at process terminatio
	dbgFlags |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(dbgFlags);
#endif // _DEBUG
	cout << "This is my client..." << endl;
	try {
		std::string const ip = "127.0.0.1";
		UDPSocket sock(8080, ip);

		cout << "Press a key to send packet." << endl;
		char ch;
		cin >> ch;

		std::string str = "Hello World!";
		sock.Send(str, ip, 49153);
	}
	catch (SocketError const& e) {
		wcout << e.what() << endl;
	}
	return 0;
}