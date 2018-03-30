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
