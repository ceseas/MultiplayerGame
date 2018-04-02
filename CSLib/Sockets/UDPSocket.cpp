#include "UDPSocket.h"

#include "../SocketAddress.h"
#include "SocketUtils.h"

UDPSocket::~UDPSocket()
{
	closesocket(_socket);
}

int UDPSocket::Bind(const SocketAddress & toAddress)
{
	int err = bind(_socket, (const sockaddr *)toAddress.GetAddressPtr(), toAddress.GetSize());
	if (err == 0)
	{
		return NO_ERROR;
	}

	SocketUtils::ReportError("UDPSocket::Bind");
	return SocketUtils::GetLastError();
}

int UDPSocket::SendTo(const void * data, int len, const SocketAddress & to)
{
	int byteSentCount = sendto(_socket, static_cast<const char *>(data), len, 0, 
								(const sockaddr *)to.GetAddressPtr(), to.GetSize());
	if (byteSentCount >= 0)
	{
		return byteSentCount;
	}
	SocketUtils::ReportError("UDPSocket::SendTo");
	return SocketUtils::GetLastError();
}

int UDPSocket::ReceiveFrom(void * buffer, int len, SocketAddress & from)
{
	int fromLength = from.GetSize();
	int readByteCount = recvfrom(_socket, static_cast<char *>(buffer), len, 0, (sockaddr *)from.GetAddressPtr(), &fromLength);
	if (readByteCount >= 0)
	{
		return readByteCount;
	}

	SocketUtils::ReportError("UDPSocket::ReceiveFrom");
	return SocketUtils::GetLastError();
}

int UDPSocket::SetNonBlockingMode(bool shouldNoneBlock)
{
#if _WIN32	
	u_long arg = shouldNoneBlock ? 1 : 0;
	int result = ioctlsocket(_socket, FIONBIO, &arg);
//#else 
//	int flags = fcntl(_socket, F_GETFL, 0);
//	flags = 
#endif

	if (result != SOCKET_ERROR)
	{
		return NO_ERROR;
	}

	SocketUtils::ReportError("UDPSOcket::SetNonBlockingMode");
	return SocketUtils::GetLastError();
}
