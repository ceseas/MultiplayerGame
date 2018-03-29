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

//void DoIt(void *param)
//{
//	SOCKET dosock = (SOCKET)param;
//	SOCKADDR_IN clientaddr = { 0, };
//	int length = sizeof(SOCKADDR_IN);
//	getpeername(dosock, (sockaddr *)&clientaddr, &length);
//
//	char msg[MAX_MSG_LEN] = "";
//	//recv함수는 상대가 소켓을 닫으면 0, 수신에 실패하면 -1을 반환한다
//	while (recv(dosock, msg, MAX_MSG_LEN, 0) > 0)
//	{
//		printf("%s : %d cleint, recv : %s\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), msg);
//		send(dosock, msg, sizeof(msg), 0);
//	}
//	closesocket(dosock);
//}
//
//void AcceptLoop(SOCKET sock)
//{
//	SOCKET dosock;
//	SOCKADDR_IN clientAddr = { 0, };
//	int length = sizeof(SOCKADDR_IN);
//	while (true)
//	{
//		dosock = accept(sock, (sockaddr *)&clientAddr, &length);
//		if (dosock == INVALID_SOCKET)
//		{
//			printf("Accept Failed\n");
//			break;
//		}
//		printf("%s:%d connection received\n", 
//			inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
//		_beginthread(DoIt, 0, (void *)dosock);
//	}
//	closesocket(sock);
//}
//

SOCKET sock_base[FD_SETSIZE];
HANDLE event_base[FD_SETSIZE];
int count = 0;

HANDLE AddNetworkEvent(SOCKET sock, long net_event)
{
	HANDLE hev = WSACreateEvent();
	sock_base[count] = sock;
	event_base[count] = hev;
	count++;

	WSAEventSelect(sock, hev, net_event);
	return hev;
}

void AcceptProc(int index)
{
	SOCKADDR_IN clientAddr = { 0, };
	int length = sizeof(SOCKADDR_IN);
	SOCKET dosock = accept(sock_base[0], (sockaddr *)&clientAddr, &length);

	if (count == FD_SETSIZE)
	{
		printf("chatting room is full!!!!\nCannnot get in...\n");
		closesocket(dosock);
		return;
	}

	AddNetworkEvent(dosock, FD_READ | FD_CLOSE);
	printf("%s : %d	 entered\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
}

void ReadProc(int index)
{
	char msg[MAX_MSG_LEN] = { 0, };
	recv(sock_base[index], msg, MAX_MSG_LEN, 0);

	SOCKADDR_IN clientAddr = { 0, };
	int length = sizeof(SOCKADDR_IN);
	getpeername(sock_base[index], (sockaddr *)&clientAddr, &length);

	char fullMsg[MAX_MSG_LEN];
	sprintf(fullMsg, "[%s : %d] : %s", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), msg);

	for (int i = 1; i < count; ++i)
	{
		if (i != index)
		{
			send(sock_base[i], fullMsg, MAX_MSG_LEN, 0);
		}
	}
}

void CloseProc(int index)
{
	SOCKADDR_IN clientAddr = { 0, };
	int length = 0;
	getpeername(sock_base[index], (sockaddr *)&clientAddr, &length);
	printf("[%s : %d] is out!!\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
	closesocket(sock_base[index]);
	WSACloseEvent(event_base[index]);

	count--;

	sock_base[index] = sock_base[count];
	event_base[index] = event_base[count];

	char msg[MAX_MSG_LEN] = {0,};
	sprintf(msg, "[%s : %d] is outttt\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
	for (int i = 1; i < count; ++i)
	{
		send(sock_base[index], msg, MAX_MSG_LEN, 0);
	}
}

void EventLoop(SOCKET sock)
{
	AddNetworkEvent(sock, FD_ACCEPT);
	while (true)
	{
		int index = WSAWaitForMultipleEvents(count, event_base, false, INFINITE, false);
		WSANETWORKEVENTS netEvents;
		WSAEnumNetworkEvents(sock_base[index], event_base[index], &netEvents);
		switch (netEvents.lNetworkEvents)
		{
		case FD_ACCEPT :
		{
			AcceptProc(index);
		}break;
		case FD_READ:
		{
			ReadProc(index);
		}break;
		case FD_CLOSE:
		{
			CloseProc(index);
		}break;
		}
	}
	closesocket(sock);
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
	else
	{
		EventLoop(sock);
	}

	WSACleanup();

	getchar();
	return 0;
}

