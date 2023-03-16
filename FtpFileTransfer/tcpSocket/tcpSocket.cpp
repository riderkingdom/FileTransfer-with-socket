#include<iostream>
#include"tcpSocket.h"
#include<WinSock2.h>

using namespace std;

bool init_Socket()
{
	//初始化代码
	WORD wVersion = MAKEWORD(2, 2);
	//MAKEWORD：将两个byte型合成一个word型，一个在高八位，一个在低八位
	//MAKEWORD(1,1)只能一次接收一次，不能马上发送，只支持TCP/IP协议，不支持异步
	//MAKEWORD(2,2)可以同时接收和发送，支持多协议，支持异步
	WSADATA wsadata;
	if (0 != WSAStartup(wVersion, &wsadata))	//WSA:widows socket ansyc	windows异步套接字
	{
		err("WSAStartup");
		return false;
	}
	//return true;
}

bool close_Socket()//反初始化操作
{
	if (0 != WSACleanup())
	{
		err("WSACleanup");
	}
	return true;
}

SOCKET create_serverSocket()
{
//1.创建一个空的socket
	//socket()无错误发生则返回引用新套接口的描述字，否则返回INVALID_SOCKET错误
	SOCKET fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	
	if (INVALID_SOCKET == fd)
	{
		err("socket");
		return INVALID_SOCKET;
	}
	//AF_INET：指定地址协议族，INET指IPV4
	//SOCK_STREAM：代表流式套接字
	//IPPROTO_TCP：指定使用TCP/IP中的协议，此处指定使用TCP协议

//2.给socket绑定本地ip地址和端口号
	struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(PORT);	//htons()：把本地字节序转成网络字节序
		addr.sin_addr.S_un.S_addr = ADDR_ANY;	//绑定本地任意ip
//3.bind绑定端口
		if (SOCKET_ERROR == bind(fd, (struct sockaddr*)&addr, sizeof(addr)))
		{
			err("bind");
			return INVALID_SOCKET;
		}

//4.开始监听
		listen(fd, 10);	//同时允许10个用户进行访问
	return fd;
}


SOCKET create_clientSocket(const char *ip)
{
	//1.创建一个空的socket
	SOCKET fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == fd)
	{
		err("socket");
		return INVALID_SOCKET;
	}
	//AF_INET：指定地址协议族，INET指IPV4
	//SOCK_STREAM：代表流式套接字
	//IPPROTO_TCP：指定使用TCP/IP中的协议，此处指定使用TCP协议

//2.给socket绑定服务端ip地址和端口号
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);	//htons()：把本地字节序转成网络字节序
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");	//绑定服务器ip
	if (INVALID_SOCKET == connect(fd, (struct sockaddr*)&addr, sizeof(addr)))
	{
		err("connect");
		return INVALID_SOCKET;
	}

	return fd;
}