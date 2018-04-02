#ifndef SOCKET_ADDRESS_H
#define SOCKET_ADDRESS_H

#include "CommonInclude.h"

class SocketAddress;
using SocketAddressPtr = std::shared_ptr<SocketAddress>;

class SocketAddress
{
public :
	SocketAddress()
	{
		_socketAddr.sin_family = AF_INET;
	}

	SocketAddress(uint32 address, uint16 port)
	{
		_socketAddr.sin_family = AF_INET;
		_socketAddr.sin_addr.s_addr = address;
		_socketAddr.sin_port = htons(port);
	}

	SocketAddress(const sockaddr &socketAddr)
	{
		memcpy(&_socketAddr, &socketAddr, sizeof(sockaddr_in));
	}

	size_t GetSize() const { return sizeof(_socketAddr); }

	sockaddr *GetAddressPtr() const { return (sockaddr *)&_socketAddr; }
	const sockaddr_in &GetAddressRef() const { return _socketAddr; }

private :
	sockaddr_in _socketAddr;
};



#endif