#include "../MultiplayerGame/Common.h"

#define PORT_NUM 10200
#define MAX_MSG_LEN	256
#define SERVER_IP "192.168.219.101"

SOCKADDR_IN sockArr;

void RecvThreadFunction(void *param)
{
	SOCKET sock = (SOCKET)param;
	char msg[MAX_MSG_LEN] = { 0, };
	while (recv(sock, msg, MAX_MSG_LEN, 0) > 0)
	{
		printf("%s\n", msg);
	}
	closesocket(sock);
}

int main()
{
	WSADATA wsaData = { 0, };
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
		return -1;
	}

	SOCKADDR_IN serveraddr = { 0, };
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	serveraddr.sin_port = htons(PORT_NUM);

	int r = 0;
	r = connect(sock, (const sockaddr *)&serveraddr, sizeof(SOCKADDR_IN));
	if (r == SOCKET_ERROR)
	{
		return -1;
	}

	int length = sizeof(SOCKADDR_IN);
	getpeername(sock, (sockaddr *)&sockArr, &length);

	_beginthread(RecvThreadFunction, 0, (void *)sock);
	char msg[MAX_MSG_LEN] = { 0, };
	while (true)
	{
		gets_s(msg, MAX_MSG_LEN);
		send(sock, msg, sizeof(msg), 0);

		if (strncmp(msg, "exit", MAX_MSG_LEN) == 0)
		{
			break;
		}
	}
	closesocket(sock);
	WSACleanup();
	return 0;
}