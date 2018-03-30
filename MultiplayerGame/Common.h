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
#include <stdint.h>
#include <malloc.h>

#include <memory>

#pragma comment(lib, "ws2_32")

IN_ADDR GetDefaultMyIP();

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

#endif