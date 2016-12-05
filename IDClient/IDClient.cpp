#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

#include <IDLib\IDLib.hpp>
using namespace IDSocket;

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <Windows.h>
#include <crtdbg.h>
#endif

mutex consoleMtx;
bool done = false;

void RecieveMessages(TCPSocket* sock)
{
	string msg;
	while (sock->IsConnected())
	{
		try
		{
			sock->Recieve(msg);
			{ lock_guard<mutex> lk(consoleMtx);
			cout << msg << endl; }
		}
		catch (SocketError const& e)
		{
			if (e.GetErrorCode() != 0)
			{
				lock_guard<mutex> lk(consoleMtx);
				cout << e.what() << endl;
			}
		}
	}
}

int main(int argc, char* argv[]) {
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

	if (argc != 2)
	{
		cout << "Must specify the Server IP to connect to." << endl;
		return 0;
	}

	string const ip(argv[1]);

	cout << "Enter your name: " << endl;
	string msg;
	getline(cin, msg);

	try {
		// Connect and submit chatroom name
		TCPSocket sock(ip, 8080);
		sock.Send(msg);

		// Start reciever thread
		thread rThread(RecieveMessages, &sock);

		while (getline(cin, msg))
		{
			if (msg == "!q")
				break;

			sock.Send(msg);
		}

		sock.Disconnect();
		rThread.join();
	}
	catch (SocketError const& e) {
		cout << e.what() << endl;
	}
	return 0;
}