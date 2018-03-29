#ifndef COMMON_H
#define COMMON_H

#include <WinSock2.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <process.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#pragma comment(lib, "ws2_32")

IN_ADDR GetDefaultMyIP();

#endif