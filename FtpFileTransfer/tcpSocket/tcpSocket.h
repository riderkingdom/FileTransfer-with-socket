#ifndef _TCPSOCKET_H_
#define _TCPSOCKET_H
#include<stdbool.h>
#include<iostream>
#include<WinSock2.h>	//头文件
#pragma comment(lib,"ws2_32.lib")	//库文件
#pragma warning(disable:4996)

#define err(errMsg)	cout<<errMsg<<"failed,code "<<WSAGetLastError()<<" line:"<<__LINE__<<endl;
#define PORT 8401	//0-1024为系统保留


//初始化网络库
bool init_Socket();

//关闭网络库
bool close_Socket();

//服务器：创建服务器socket
SOCKET create_serverSocket();

//客户端：创建客户端socket
SOCKET create_clientSocket(const char *ip);
#endif