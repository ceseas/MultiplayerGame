#include "UDPSocket.h"

#include "SocketUtil.h"

UDPSocket::~UDPSocket()
{
	closesocket(_socket);
}

int UDPSocket::Bind(const SocketAddress & toAddress)
{
	int err = bind(_socket, (const sockaddr *)&toAddress._socketAddr, toAddress.GetSize());
	if (err == 0)
	{
		return NO_ERROR;
	}

	SocketUtil::ReportError("UDPSocket::Bind");
	return SocketUtil::GetLastError();
}

int UDPSocket::SendTo(const void * data, int len, const SocketAddress & to)
{
	int byteSentCount = sendto(_socket, static_cast<const char *>(data), len, 0, 
								(const sockaddr *)&to._socketAddr, to.GetSize());
	if (byteSentCount >= 0)
	{
		return byteSentCount;
	}
	SocketUtil::ReportError("UDPSocket::SendTo");
	return SocketUtil::GetLastError();
}

int UDPSocket::ReceiveFrom(void * buffer, int len, SocketAddress & from)
{
	int fromLength = from.GetSize();
	int readByteCount = recvfrom(_socket, static_cast<char *>(buffer), len, 0, (sockaddr *)&from._socketAddr, &fromLength);
	if (readByteCount >= 0)
	{
		return readByteCount;
	}

	SocketUtil::ReportError("UDPSocket::ReceiveFrom");
	return SocketUtil::GetLastError();
}
