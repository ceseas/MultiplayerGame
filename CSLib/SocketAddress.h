#ifndef SOCKET_ADDRESS_H
#define SOCKET_ADDRESS_H

#include "CSLib.h"

class SocketAddress;
using SocketAddressPtr = std::shared_ptr<SocketAddress>;

class SocketAddress
{
public :
	SocketAddress(uint32 address, uint16 port)
	{
		_socketAddr.sin_family = AF_INET;
		_socketAddr.sin_addr.s_addr = htonl(address);
		_socketAddr.sin_port = htons(port);
	}

	SocketAddress(const sockaddr &socketAddr)
	{
		memcpy(&_socketAddr, &socketAddr, sizeof(sockaddr_in));
	}

	size_t GetSize() const { return sizeof(_socketAddr); }

	sockaddr *GetAddressPtr() const { return (sockaddr *)&_socketAddr; }
	sockaddr_in &GetAddressRef() { return _socketAddr; }

private :
	sockaddr_in _socketAddr;
};



#endif