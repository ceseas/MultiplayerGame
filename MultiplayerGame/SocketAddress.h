#ifndef SOCKET_ADDRESS_H
#define SOCKET_ADDRESS_H

#include <WinSock2.h>
#include <memory>
#include "TypeDef.h"

class SocketAddress;
using SocketAddressPtr = std::shared_ptr<SocketAddress>;

class SocketAddress
{
public :
	SocketAddress(uint32 address, uint16 port)
	{
		GetSockAddrIn()->sin_family = AF_INET;
		GetSockAddrIn()->sin_addr.s_addr = htonl(address);
		GetSockAddrIn()->sin_port = htons(port);
	}

	SocketAddress(const sockaddr &socketAddr)
	{
		memcpy(&_socketAddr, &socketAddr, sizeof(sockaddr_in));
	}

	size_t GetSize() const
	{
		return sizeof(_socketAddr);
	}

	sockaddr_in _socketAddr;

private :

	sockaddr_in *GetSockAddrIn()
	{
		return &_socketAddr;
	}
};



#endif