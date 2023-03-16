#ifndef _TCPSOCKET_H_
#define _TCPSOCKET_H
#include<stdbool.h>
#include<iostream>
#include<WinSock2.h>	//ͷ�ļ�
#pragma comment(lib,"ws2_32.lib")	//���ļ�
#pragma warning(disable:4996)

#define err(errMsg)	cout<<errMsg<<"failed,code "<<WSAGetLastError()<<" line:"<<__LINE__<<endl;
#define PORT 8401	//0-1024Ϊϵͳ����


//��ʼ�������
bool init_Socket();

//�ر������
bool close_Socket();

//������������������socket
SOCKET create_serverSocket();

//�ͻ��ˣ������ͻ���socket
SOCKET create_clientSocket(const char *ip);
#endif