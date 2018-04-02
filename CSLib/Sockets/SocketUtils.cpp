#include "SocketUtils.h"

void SocketUtils::ReportError(const char * s)
{
}

int SocketUtils::GetLastError()
{
	return WSAGetLastError();
}

UDPSocketSPtr SocketUtils::CreateUDPSocket(SocketAddressFamily family)
{
	SOCKET s = socket(family, SOCK_DGRAM, IPPROTO_UDP);
	if (s != INVALID_SOCKET)
	{
		return UDPSocketSPtr(new UDPSocket(s));
	}
	ReportError("SocketUtils::CreateUDPSocket");
	return nullptr;
}

TCPSocketSPtr SocketUtils::CreateTCPSocket(SocketAddressFamily family)
{
	return TCPSocketSPtr();
}

fd_set * SocketUtils::FillSetFromVector(fd_set & set, const std::vector<TCPSocketSPtr>* sockets)
{
	if (sockets != nullptr)
	{
		FD_ZERO(&set);
		for (const TCPSocketSPtr &sock : *sockets)
		{
			FD_SET(sock->_socket, &set);
		}
		return &set;
	}
	else
	{
		return nullptr;
	}
}

void SocketUtils::FillVectorFromSet(std::vector<TCPSocketSPtr>* outSockets, 
									const std::vector<TCPSocketSPtr>* inSockets, 
									const fd_set & set)
{
	if (inSockets != nullptr && outSockets != nullptr)
	{
		outSockets->clear();
		for (const TCPSocketSPtr &sock : *inSockets)
		{
			if (FD_ISSET(sock->_socket, &set))
			{
				outSockets->push_back(sock);
			}
		}
	}
}

int SocketUtils::Select(const std::vector<TCPSocketSPtr>* inReadSet, std::vector<TCPSocketSPtr>* outReadSet, 
						const std::vector<TCPSocketSPtr>* inWriteSet, std::vector<TCPSocketSPtr>* outWriteSet, 
						const std::vector<TCPSocketSPtr>* inExceptSet, std::vector<TCPSocketSPtr>* outExceptSet)
{
	fd_set read, write, except;
	fd_set *readPtr = FillSetFromVector(read, inReadSet);
	fd_set *writePtr = FillSetFromVector(write, inWriteSet);
	fd_set *exceptPtr = FillSetFromVector(except, inExceptSet);

	int toRet = select(0, readPtr, writePtr, exceptPtr, nullptr);
	if (toRet > 0)
	{
		FillVectorFromSet(outReadSet, inReadSet, read);
		FillVectorFromSet(outWriteSet, inWriteSet, write);
		FillVectorFromSet(outExceptSet, inExceptSet, except);
	}
	return toRet;
}
