#include "Common.h"

int main()
{

	sockaddr_in add = { 0, };
	add.sin_family = AF_INET;
	add.sin_port = htons(1020);
	InetPton(AF_INET, "172.30.1.32", &add.sin_addr);

	addrinfo *info;
	getaddrinfo("gpnbs.blogspot.kr/", "http", nullptr, &info);

	freeaddrinfo(info);

	return 0;
}

