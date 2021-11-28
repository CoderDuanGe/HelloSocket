#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<Windows.h>
#include<WinSock2.h>
#include <stdio.h>

//#pragma comment(lib,"ws2_32.lib")
int main()
{
	//启动windows sock2.x环境
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);

	//	1. 建立一个socket
	SOCKET _sock=socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == _sock)
	{
		printf("sock bulid errno\n");
	}
	else
	{
		printf("sock bulid success\n");
	}
	//	2. 连接服务器connect
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	int ret=connect(_sock, (sockaddr*)&_sin, sizeof(sockaddr_in));
	if (SOCKET_ERROR == ret)
	{
		printf("connect errno\n");
	}
	else
	{
		printf("connect success\n");
	}
	//	3. 接受服务器信息 recv
	char recvBuf[256] = {};
	int nlen=recv(_sock, recvBuf, sizeof(recvBuf), 0);
	if (nlen > 0)
	{
		printf("accept data : %s\n", recvBuf);
	}
	//	4. 关闭socket closesocket
	closesocket(_sock);
	//清楚windows socket环境
	WSACleanup();
	getchar();
	return 0;
}