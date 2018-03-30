#ifndef UDP_SOCKET_H
#define UDP_SOCKET_H

#include "SocketAddress.h"

//#include "Common.h"

class UDPSocket
{
public :
	~UDPSocket();

	int Bind(const SocketAddress &toAddress);
	int SendTo(const void *data, int len, const SocketAddress &to);
	int ReceiveFrom(void *buffer, int len, SocketAddress &from);

	int SetNonBlockingMode(bool shouldNoneBlock);

private :

	friend class SocketUtil;
	UDPSocket(SOCKET socket) 
		:_socket(socket)
	{
	}
	SOCKET _socket;
};

using UDPSocketPtr = std::shared_ptr<UDPSocket>;

#endif 
