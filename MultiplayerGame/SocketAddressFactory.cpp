#include "SocketAddressFactory.h"
#include "Common.h"

SocketAddressPtr SocketAddressFactory::CreateIPv4FromString(const std::string & s)
{
	auto pos = s.find_last_of(':');
	std::string host, service;
	if (pos != std::string::npos)
	{
		host = s.substr(0, pos);
		service = s.substr(pos + 1);
	}
	else
	{
		host = s;
		service = "0";
	}

	addrinfo hint = { 0, };
	hint.ai_family = AF_INET;

	addrinfo *result = nullptr;
	int error = getaddrinfo(host.c_str(), service.c_str(), &hint, &result);
	addrinfo *initResult = result;
	if (error != ERROR_SUCCESS && result != nullptr)
	{
		freeaddrinfo(initResult);
		return nullptr;
	}

	while (!result->ai_addr && result->ai_next != nullptr)
	{
		result = result->ai_next;
	}

	if (!result->ai_addr)
	{
		freeaddrinfo(initResult);
		return nullptr;
	}

	auto toRet = std::make_shared<SocketAddress>(*result->ai_addr);
	freeaddrinfo(initResult);
	return toRet;
}