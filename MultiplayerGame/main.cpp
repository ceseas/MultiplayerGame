#include "stdafx.h"

bool gServerRunning = false;

NetworkManager gManager;

void ProcessNewClient(TCPSocketSPtr sock, const SocketAddress &address)
{
	std::cout << "client : " << inet_ntoa(address.GetAddressRef().sin_addr) << " welcome" << std::endl;
}

void ProcessDataFromClient(TCPSocketSPtr sock, const void *buffer, int byteReceived, 
							const std::vector<TCPSocketSPtr> &readables)
{
	std::cout << "Received data : " << static_cast<const char *>(buffer) << std::endl;
	for (int i = 1; i < readables.size(); ++i)
	{
		if (readables[i] != sock)
		{
			readables[i]->Send(buffer, byteReceived);
		}
	}
}

int main()
{
	gManager.Init();

	SocketAddress address(inet_addr("192.168.219.154"), 1020);
	TCPSocketSPtr listenSocket = SocketUtils::CreateTCPSocket(SocketAddressFamily::INET); 

	if (listenSocket->Bind(address) != NO_ERROR)
	{
		std::cout << "Bind Error" << std::endl;
		return 0;
	}

	if (listenSocket->Listen() != NO_ERROR)
	{
		std::cout << "Listen Error" << std::endl;
		return 0;
	}

	std::vector<TCPSocketSPtr> readBlockSockets;
	readBlockSockets.push_back(listenSocket);
	std::vector<TCPSocketSPtr> readableSockets;

	gServerRunning = true;

	while (gServerRunning)
	{
		if (!SocketUtils::Select(&readBlockSockets, &readableSockets,
			nullptr, nullptr,
			nullptr, nullptr))
		{
			continue;
		}

		for (const TCPSocketSPtr &sock : readableSockets)
		{
			if (sock == listenSocket)
			{
				SocketAddress newClientAddress;
				TCPSocketSPtr newSocket = listenSocket->Accept(newClientAddress);
				readBlockSockets.push_back(newSocket);
				ProcessNewClient(newSocket, newClientAddress);
			}
			else
			{
				//일반 소켓이므로 데이터를 수신한다.
				char buffer[256] = { 0, };
				int byteReceived = sock->Receive(buffer, sizeof(buffer));
				if (byteReceived > 0)
				{
					ProcessDataFromClient(sock, buffer, byteReceived, readBlockSockets);
				}
			}
		}
	}

	gManager.Shutdown();
	return 0;
}

