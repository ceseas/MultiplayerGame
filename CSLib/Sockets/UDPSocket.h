#ifndef UDP_SOCKET_H
#define UDP_SOCKET_H

class SocketAddress;
#include "Sockets.h"

class UDPSocket;
using UDPSocketSPtr = std::shared_ptr<UDPSocket>;

class UDPSocket
{
public :
	~UDPSocket();

	int Bind(const SocketAddress &toAddress);
	int SendTo(const void *data, int len, const SocketAddress &to);
	int ReceiveFrom(void *buffer, int len, SocketAddress &from);

	int SetNonBlockingMode(bool shouldNoneBlock);

private :

	friend class SocketUtils;
	UDPSocket(SOCKET socket) 
		:_socket(socket)
	{
	}
	SOCKET _socket;
};


#endif 
