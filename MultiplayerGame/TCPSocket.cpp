#include "TCPSocket.h"

#include "SocketUtil.h"

TCPSocket::~TCPSocket()
{
	closesocket(_socket);
}

int TCPSocket::Connect(const SocketAddress & address)
{
	int err = connect(_socket, (const sockaddr *)&address._socketAddr, address.GetSize());
	if (err >= 0)
	{
	
		return NO_ERROR;
	}
	SocketUtil::ReportError("TCPSocket::Connect");
	return SocketUtil::GetLastError();
}

int TCPSocket::Bind(const SocketAddress & address)
{
	int err = bind(_socket, (const sockaddr *)&address._socketAddr, address.GetSize());
	if (err == 0)
	{
		return NO_ERROR;
	}

	SocketUtil::ReportError("TCP::Bind");
	return SocketUtil::GetLastError();
}

int TCPSocket::Listen(int backLog)
{
	int err = listen(_socket, backLog);
	if (err >= 0)
	{
		return NO_ERROR;
	}
	SocketUtil::ReportError("TCPSocket::Listen");
	return SocketUtil::GetLastError();
}

TCPSocketPtr TCPSocket::Accept(SocketAddress & fromAddress)
{
	int length = fromAddress.GetSize();
	SOCKET newSocket = accept(_socket, (sockaddr *)&fromAddress._socketAddr, &length);
	if (newSocket != INVALID_SOCKET)
	{
		return TCPSocketPtr(new TCPSocket(newSocket));
	}
	SocketUtil::ReportError("TCPSocket::Accept");
	return nullptr;
}

int TCPSocket::Send(const void * data, int len)
{
	int byteSentCount = send(_socket, static_cast<const char *>(data), len, 0);
	if (byteSentCount >= 0)
	{
		return byteSentCount;
	}
	SocketUtil::ReportError("TCPSocket::Send");
	return SocketUtil::GetLastError();
}

int TCPSocket::Receive(void * buffer, int len)
{
	int byteReceivedCount = recv(_socket, static_cast<char *>(buffer), len, 0);
	if (byteReceivedCount >= 0)
	{
		return byteReceivedCount;
	}
	SocketUtil::ReportError("TCPSocket::Receive");
	return SocketUtil::GetLastError();
}
