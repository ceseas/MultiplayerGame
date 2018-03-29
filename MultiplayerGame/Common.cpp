#include "Common.h"

IN_ADDR GetDefaultMyIP()
{
	char localHostName[MAX_PATH];
	IN_ADDR result = { 0, };

	if (gethostname(localHostName, MAX_PATH) == SOCKET_ERROR)
	{
		return result;
	}

	HOSTENT *ptr = gethostbyname(localHostName);
	while (ptr && ptr->h_name)
	{
		if (ptr->h_addrtype == PF_INET)
		{
			memcpy(&result, ptr->h_addr_list[0], ptr->h_length);
			break;
		}
	}
	return result;
}
