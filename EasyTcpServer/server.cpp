#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS //inet_ntoa�Ѿ��������ˣ��������������ʹ��
#include<Windows.h>
#include<WinSock2.h>
#include<stdio.h>

//#pragma comment(lib,"ws2_32.lib")
int main()
{
	//����windows sock2.x����
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);
	//	1. ����һ��socket �׽���
	SOCKET _sock=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//	2. �󶨽��ܿͻ������ӵĶ˿�bind
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);//htons(ת�������ֽ���)
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;//inet_addr("127.0.0.1");
	if (SOCKET_ERROR == bind(_sock, (sockaddr*)&_sin, sizeof(_sin)))
	{
		printf("errno bind...\n");
	}
	else
	{
		printf("success bind...\n");
	}
	//	3. ��������˿� listen
	if (SOCKET_ERROR == listen(_sock, 5))
	{
		printf("errno listen...\n");
	}
	else
	{
		printf("success listen...\n");
	}

	//	4. �ȴ����ܿͻ�������accept
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
		//	5. ��ͻ��˷���һ������send	
		//���͵�ʱ�򲻻ᷢ��'\0'���ʶ�����+1
		send(_cSock, msgBuf, strlen(msgBuf) + 1, 0);
	}
	//	6. �ر�socket closesocket
	closesocket(_sock);
	//���windows socket����
	WSACleanup();
	return 0;
}