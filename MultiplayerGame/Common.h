#ifndef COMMON_H
#define COMMON_H

#include <WinSock2.h>
#include <WS2tcpip.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <process.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <malloc.h>

//STL Containers
#include <vector>
#include <unordered_map>

#include <memory>

#pragma comment(lib, "ws2_32")

IN_ADDR GetDefaultMyIP();

#define OFFSETOF(c, m) ((size_t) & (static_cast<c *>(nullptr)->m))

class GameObject;

enum PacketType
{
	PT_Hello,
	PT_ReplicationData,
	PT_Disconnect,
	PT_MAX,
};

#include "SocketAddress.h"
#include "SocketAddressFactory.h"

#include "UDPSocket.h"
#include "TCPSocket.h"
#include "SocketUtil.h"

#include "ByteSwap.h"
#include "InputMemoryStream.h"
#include "OutputMemoryStream.h"

#include "LinkingContext.h"

#include "Reflections.h"

#include "ObjectCreationRegistry.h"

#endif