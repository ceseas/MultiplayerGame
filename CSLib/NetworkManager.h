#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include "CommonInclude.h"

class NetworkManager
{
public :
	virtual ~NetworkManager()
	{
	}

	int Init();

	int Shutdown();

private:

};

#endif