#ifndef __FILEOP_H_
#define __FILEOP_H_

#include"tcpSocket.h"
#define _CRT_SECURE_NO_WARNINGS

/***�����***/
//�����ļ�
bool sendFile(SOCKET s, const char* fileName);

/***�ͻ���***/
//�����ļ�
bool recvFile(SOCKET s, const char* fileName);


#endif

