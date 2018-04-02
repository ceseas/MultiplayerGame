#ifndef CS_LIB_H
#define CS_LIB_H

#include <WinSock2.h>
#pragma comment (lib, "ws2_32")

#include <string>
#include <vector>
#include <memory>

#include <stdint.h>

using uint8 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

using int8 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;


#include "SocketAddress.h"

#include "Sockets\Sockets.h"

#endif