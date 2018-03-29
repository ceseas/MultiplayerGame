#include "Common.h"

#define PORT_NUM 10200
#define BLOG_SIZE 5
#define MAX_MSG_LEN 256

SOCKET SetTCPServer(short portNum, int blog)
{
	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
		return -1;
	}
	SOCKADDR_IN serveraddr = { 0, };
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr = GetDefaultMyIP();
	serveraddr.sin_port = htons(portNum);

	int r = bind(sock, (const sockaddr *)&serveraddr, sizeof(SOCKADDR_IN));
	if (r == SOCKET_ERROR)
	{
		return -1;
	}
	r = listen(sock, BLOG_SIZE);
	if (r == SOCKET_ERROR)
	{
		return -1;
	}
	return sock;
}

void DoIt(void *param)
{
	SOCKET dosock = (SOCKET)param;
	SOCKADDR_IN clientaddr = { 0, };
	int length = sizeof(SOCKADDR_IN);
	getpeername(dosock, (sockaddr *)&clientaddr, &length);

	char msg[MAX_MSG_LEN] = "";
	//recv함수는 상대가 소켓을 닫으면 0, 수신에 실패하면 -1을 반환한다
	while (recv(dosock, msg, MAX_MSG_LEN, 0) > 0)
	{
		printf("%s : %d cleint, recv : %s\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), msg);
		send(dosock, msg, sizeof(msg), 0);
	}
	closesocket(dosock);
}

void AcceptLoop(SOCKET sock)
{
	SOCKET dosock;
	SOCKADDR_IN clientAddr = { 0, };
	int length = sizeof(SOCKADDR_IN);
	while (true)
	{
		dosock = accept(sock, (sockaddr *)&clientAddr, &length);
		if (dosock == INVALID_SOCKET)
		{
			printf("Accept Failed\n");
			break;
		}
		printf("%s:%d connection received\n", 
			inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
		_beginthread(DoIt, 0, (void *)dosock);
	}
	closesocket(sock);
}

void ThreadFunction(void *param)
{

	int id = *(reinterpret_cast<int *>(param));

	for (int i = 0; i < id; ++i)
	{
		printf("Thread function : %d\n", i);
	}
}

int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET sock = SetTCPServer(PORT_NUM, BLOG_SIZE);
	if (sock == -1)
	{
		printf("cannot create tcp server\n");
		WSACleanup();
		return 0;
	}
	AcceptLoop(sock);

	WSACleanup();

	getchar();
	return 0;
}

