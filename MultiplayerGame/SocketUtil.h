#ifndef SOCKET_UTIL_H
#define SOCKET_UTIL_H

#include "Common.h"

#include "UDPSocket.h"

enum SocketAddressFamily
{
	INET  = AF_INET,
	INET6 = AF_INET6,
};

class SocketUtil
{
public :

	static void ReportError(const char *s);
	static int GetLastError();

	static UDPSocketPtr CreateUDPSocket(SocketAddressFamily family);


private :

};

#endif