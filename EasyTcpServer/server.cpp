#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS //inet_ntoa已经被废弃了，用这个宏来继续使用
#include<Windows.h>
#include<WinSock2.h>
#include<stdio.h>

//#pragma comment(lib,"ws2_32.lib")
int main()
{
	//启动windows sock2.x环境
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);
	//	1. 建立一个socket 套接字
	SOCKET _sock=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//	2. 绑定接受客户端连接的端口bind
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);//htons(转换网络字节序)
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;//inet_addr("127.0.0.1");
	if (SOCKET_ERROR == bind(_sock, (sockaddr*)&_sin, sizeof(_sin)))
	{
		printf("errno bind...\n");
	}
	else
	{
		printf("success bind...\n");
	}
	//	3. 监听网络端口 listen
	if (SOCKET_ERROR == listen(_sock, 5))
	{
		printf("errno listen...\n");
	}
	else
	{
		printf("success listen...\n");
	}

	//	4. 等待接受客户端连接accept
	sockaddr_in clientAddr={};
	int nAddrLen = sizeof(sockaddr_in);
	SOCKET _cSock = INVALID_SOCKET;
	char msgBuf[] = "Hello,I'm Server.";
	while (true)
	{
		_cSock = accept(_sock, (sockaddr*)&clientAddr, &nAddrLen);
		if (INVALID_SOCKET == _cSock)
		{
			printf("errno accept...\n");
		}
		printf("new server join: IP = %s \n", inet_ntoa(clientAddr.sin_addr));
		//	5. 向客户端发送一条数据send	
		//发送的时候不会发送'\0'，故而长度+1
		send(_cSock, msgBuf, strlen(msgBuf) + 1, 0);
	}
	//	6. 关闭socket closesocket
	closesocket(_sock);
	//清除windows socket环境
	WSACleanup();
	return 0;
}