#ifndef SOCKET_ADDRESS_FACTORY_H
#define SOCKET_ADDRESS_FACTORY_H

#include "SocketAddress.h"
#include <string>

class SocketAddressFactory
{
public :
	static SocketAddressPtr CreateIPv4FromString(const std::string &s);
	
private :

};

#endif