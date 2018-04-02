#include "TCPSocket.h"

#include "../SocketAddress.h"
#include "SocketUtils.h"

TCPSocket::~TCPSocket()
{
	closesocket(_socket);
}

int TCPSocket::Connect(const SocketAddress & address)
{
	int err = connect(_socket, (const sockaddr *)address.GetAddressPtr(), address.GetSize());
	if (err >= 0)
	{
	
		return NO_ERROR;
	}
	SocketUtils::ReportError("TCPSocket::Connect");
	return SocketUtils::GetLastError();
}

int TCPSocket::Bind(const SocketAddress & address)
{
	int err = bind(_socket, (const sockaddr *)address.GetAddressPtr(), address.GetSize());
	if (err == 0)
	{
		return NO_ERROR;
	}

	SocketUtils::ReportError("TCP::Bind");
	return SocketUtils::GetLastError();
}

int TCPSocket::Listen(int backLog)
{
	int err = listen(_socket, backLog);
	if (err >= 0)
	{
		return NO_ERROR;
	}
	SocketUtils::ReportError("TCPSocket::Listen");
	return SocketUtils::GetLastError();
}

TCPSocketSPtr TCPSocket::Accept(SocketAddress & fromAddress)
{
	int length = fromAddress.GetSize();
	SOCKET newSocket = accept(_socket, (sockaddr *)fromAddress.GetAddressPtr(), &length);
	if (newSocket != INVALID_SOCKET)
	{
		return TCPSocketSPtr(new TCPSocket(newSocket));
	}
	SocketUtils::ReportError("TCPSocket::Accept");
	return nullptr;
}

int TCPSocket::Send(const void * data, int len)
{
	int byteSentCount = send(_socket, static_cast<const char *>(data), len, 0);
	if (byteSentCount >= 0)
	{
		return byteSentCount;
	}
	SocketUtils::ReportError("TCPSocket::Send");
	return SocketUtils::GetLastError();
}

int TCPSocket::Receive(void * buffer, int len)
{
	int byteReceivedCount = recv(_socket, static_cast<char *>(buffer), len, 0);
	if (byteReceivedCount >= 0)
	{
		return byteReceivedCount;
	}
	SocketUtils::ReportError("TCPSocket::Receive");
	return SocketUtils::GetLastError();
}
