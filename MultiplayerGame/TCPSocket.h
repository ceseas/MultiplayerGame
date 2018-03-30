#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H

//#include "Common.h"
#include "SocketAddress.h"


class TCPSocket;
using TCPSocketPtr = std::shared_ptr<TCPSocket>;

class TCPSocket
{
public :
	~TCPSocket();

	int Connect(const SocketAddress &address);
	int Bind(const SocketAddress &address);
	int Listen(int backLog = 32);
	TCPSocketPtr Accept(SocketAddress &fromAddress);
	int Send(const void *data, int len);
	int Receive(void *buffer, int len);

private :

	friend class SocketUtil;

	TCPSocket(SOCKET sock)
		:_socket(sock)
	{
	}
	SOCKET _socket;
};


#endif