#include "Common.h"

int main()
{
	WSAData data = { 0, };
	WSAStartup(MAKEWORD(2, 2), &data);



	sockaddr_in add = { 0, };
	add.sin_family = AF_INET;
	add.sin_port = htons(1020);
	InetPtonA(AF_INET, "172.30.1.32", &add.sin_addr);

	addrinfo *info;
	getaddrinfo("gpnbs.blogspot.kr/", "http", nullptr, &info);

	freeaddrinfo(info);

	WSACleanup();

	return 0;
}

