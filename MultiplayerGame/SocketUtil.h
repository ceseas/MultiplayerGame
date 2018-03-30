#ifndef SOCKET_UTIL_H
#define SOCKET_UTIL_H

#include "Common.h"

#include "UDPSocket.h"
#include "TCPSocket.h"

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

	static fd_set *FillSetFromVector(fd_set &set, const std::vector<TCPSocketPtr> *sockets);
	static void FillVectorFromSet(std::vector<TCPSocketPtr> *outSockets, 
								  const std::vector<TCPSocketPtr> *inSockets, 
								  const fd_set &set);
	static int Select(const std::vector<TCPSocketPtr> *inReadSet, std::vector<TCPSocketPtr> *outReadSet,
					  const std::vector<TCPSocketPtr> *inWriteSet, std::vector<TCPSocketPtr> *outWriteSet,
					  const std::vector<TCPSocketPtr> *inExceptSet, std::vector<TCPSocketPtr> *outExceptSet);


private :

};

#endif