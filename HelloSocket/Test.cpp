#define WIN32_LEAN_AND_MEAN
#include<Windows.h>
#include<WinSock2.h>

//#pragma comment(lib,"ws2_32.lib")
int main()
{
	//启动windows sock2.x环境
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver,&dat);



	//清楚windows socket环境
	WSACleanup();
	return 0;
}