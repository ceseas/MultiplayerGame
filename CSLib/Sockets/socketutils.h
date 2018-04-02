#ifndef SOCKET_UTILS_H
#define SOCKET_UTILS_H

//#include "Sockets.h"

#include "TCPSocket.h"
#include "UDPSocket.h"

enum SocketAddressFamily
{
	INET  = AF_INET,
	INET6 = AF_INET6,
};

class SocketUtils
{
public :

	static void ReportError(const char *s);
	static int GetLastError();

	static UDPSocketSPtr CreateUDPSocket(SocketAddressFamily family);
	static TCPSocketSPtr CreateTCPSocket(SocketAddressFamily family);

	static fd_set *FillSetFromVector(fd_set &set, const std::vector<TCPSocketSPtr> *sockets);
	static void FillVectorFromSet(std::vector<TCPSocketSPtr> *outSockets, 
								  const std::vector<TCPSocketSPtr> *inSockets, 
								  const fd_set &set);
	static int Select(const std::vector<TCPSocketSPtr> *inReadSet, std::vector<TCPSocketSPtr> *outReadSet,
					  const std::vector<TCPSocketSPtr> *inWriteSet, std::vector<TCPSocketSPtr> *outWriteSet,
					  const std::vector<TCPSocketSPtr> *inExceptSet, std::vector<TCPSocketSPtr> *outExceptSet);


private :

};

#endif