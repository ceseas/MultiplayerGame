#include "SocketUtil.h"

void SocketUtil::ReportError(const char * s)
{
}

int SocketUtil::GetLastError()
{
	return WSAGetLastError();
}

UDPSocketPtr SocketUtil::CreateUDPSocket(SocketAddressFamily family)
{
	SOCKET s = socket(family, SOCK_DGRAM, IPPROTO_UDP);
	if (s != INVALID_SOCKET)
	{
		return UDPSocketPtr(new UDPSocket(s));
	}
	ReportError("SocketUtil::CreateUDPSocket");
	return nullptr;
}

fd_set * SocketUtil::FillSetFromVector(fd_set & set, const std::vector<TCPSocketPtr>* sockets)
{
	if (sockets != nullptr)
	{
		FD_ZERO(&set);
		for (const TCPSocketPtr &socket : *sockets)
		{
			FD_SET(socket->_socket, &set);
		}
		return &set;
	}
	else
	{
		return nullptr;
	}
}

void SocketUtil::FillVectorFromSet(std::vector<TCPSocketPtr>* outSockets, 
									const std::vector<TCPSocketPtr>* inSockets, 
									const fd_set & set)
{
	if (inSockets != nullptr && outSockets != nullptr)
	{
		outSockets->clear();
		for (const TCPSocketPtr &sock : *inSockets)
		{
			if (FD_ISSET(sock->_socket, &set))
			{
				outSockets->push_back(sock);
			}
		}
	}
}

int SocketUtil::Select(const std::vector<TCPSocketPtr>* inReadSet, std::vector<TCPSocketPtr>* outReadSet, 
						const std::vector<TCPSocketPtr>* inWriteSet, std::vector<TCPSocketPtr>* outWriteSet, 
						const std::vector<TCPSocketPtr>* inExceptSet, std::vector<TCPSocketPtr>* outExceptSet)
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
