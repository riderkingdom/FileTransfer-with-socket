#ifndef __FILEOP_H_
#define __FILEOP_H_

#include"tcpSocket.h"
#define _CRT_SECURE_NO_WARNINGS

/***服务端***/
//发送文件
bool sendFile(SOCKET s, const char* fileName);

/***客户端***/
//接受文件
bool recvFile(SOCKET s, const char* fileName);


#endif

