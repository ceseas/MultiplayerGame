#include "stdafx.h"


bool gRunning = false;

void ReceiveMessage(TCPSocketSPtr sock)
{
	char buffer[256] = { 0, };
	while (gRunning)
	{
		if (sock->Receive(buffer, sizeof(buffer)) > 0)
		{
			std::cout << buffer << std::endl;
		}
		ZeroMemory(buffer, sizeof(buffer));
	}
}

int main()
{

	NetworkManager manager;
	manager.Init();

	SocketAddress address(inet_addr("192.168.219.154"), 1020);
	TCPSocketSPtr sock = SocketUtils::CreateTCPSocket(SocketAddressFamily::INET);

	//sock->SetNonBlockingMode(true);

	if (sock->Connect(address) == NO_ERROR)
	{
		gRunning = true;
	}

	std::thread receiveThread(ReceiveMessage, sock);

	char buffer[256] = { 0, };
	while (gRunning)
	{
		std::string s;
		std::cin >> s;

		if (s == "exit")
		{
			gRunning = false;
		}

		sprintf(buffer, "%s", s.c_str());
		if (sock->Send(buffer, sizeof(buffer)) > 0)
		{
		}
		ZeroMemory(buffer, sizeof(buffer));
	}

	receiveThread.join();

	manager.Shutdown();

	int a = 0;
	std::cin >> a;
	return 0;
}