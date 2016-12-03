// STL headers
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <thread>
using namespace std;

// IDSocket headers
#include <IDLib\IDLib.hpp>
using namespace IDSocket;

// Windows headers
#include <Windows.h>

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

std::string const localhost = "127.0.0.1";

TCPListener listener;
map<string, shared_ptr<TCPSocket>> mClients;
vector<thread> vThreads;
bool isRunning = true;

// Functions
bool CtrlHandler(DWORD ctrlType)
{
	if (ctrlType == CTRL_C_EVENT)
	{
		isRunning = false;
		listener.Close();
		return TRUE;
	}
	return FALSE;
}

void RelayInput(string name)
{
	auto& sClient = mClients.at(name);
	string msg;
	while (sClient->IsConnected())
	{
		try
		{
			// Get a chat message from this client
			sClient->Recieve(msg);

			// Send the message to all clients
			for (auto& client : mClients)
			{
				if (client.second->IsConnected())
				{
					ostringstream oss;
					oss << name << ": " << msg;
					client.second->Send(oss.str());
				}
			}
		}
		catch (SocketError const& e)
		{
			if (e.GetErrorCode() != 0)
				cout << e.what() << endl;
		}
	}
	cout << name << " left.";
}

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

	if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE))
	{
		cout << "Could not register the CTRL-C handler." << endl;
		return 0;
	}

	cout << "IDChat Server 1.0" << endl;

	// Listener thread
	listener.Listen(localhost, 8080);
	while (isRunning)
	{
		try
		{
			shared_ptr<TCPSocket> client = listener.Accept();
			string name;
			client->Recieve(name);

			cout << name << " joined." << endl;

			mClients.insert(pair<string, shared_ptr<TCPSocket>>(name, client));
			vThreads.push_back(thread(RelayInput, name));
		}
		catch (SocketError const& e)
		{
			if (e.GetErrorCode() != 0)
				cout << e.what() << endl;
			isRunning = false;
		}
	}

	// Rejoin threads
	for (auto& t : vThreads)
		t.join();

	return 0;
}