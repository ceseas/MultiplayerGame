#include "NetworkManager.h"


int NetworkManager::Init()
{
	WSADATA startupData = { 0, };
	int error = WSAStartup(MAKEWORD(2, 2), &startupData);
	if (error == NO_ERROR)
	{
		return NO_ERROR;
	}

	return WSAGetLastError();
}

int NetworkManager::Shutdown()
{
	int error = WSACleanup();
	return error;
}
