#include<iostream>
#include"tcpSocket.h"
#include<WinSock2.h>

using namespace std;

bool init_Socket()
{
	//��ʼ������
	WORD wVersion = MAKEWORD(2, 2);
	//MAKEWORD��������byte�ͺϳ�һ��word�ͣ�һ���ڸ߰�λ��һ���ڵͰ�λ
	//MAKEWORD(1,1)ֻ��һ�ν���һ�Σ��������Ϸ��ͣ�ֻ֧��TCP/IPЭ�飬��֧���첽
	//MAKEWORD(2,2)����ͬʱ���պͷ��ͣ�֧�ֶ�Э�飬֧���첽
	WSADATA wsadata;
	if (0 != WSAStartup(wVersion, &wsadata))	//WSA:widows socket ansyc	windows�첽�׽���
	{
		err("WSAStartup");
		return false;
	}
	//return true;
}

bool close_Socket()//����ʼ������
{
	if (0 != WSACleanup())
	{
		err("WSACleanup");
	}
	return true;
}

SOCKET create_serverSocket()
{
//1.����һ���յ�socket
	//socket()�޴������򷵻��������׽ӿڵ������֣����򷵻�INVALID_SOCKET����
	SOCKET fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	
	if (INVALID_SOCKET == fd)
	{
		err("socket");
		return INVALID_SOCKET;
	}
	//AF_INET��ָ����ַЭ���壬INETָIPV4
	//SOCK_STREAM��������ʽ�׽���
	//IPPROTO_TCP��ָ��ʹ��TCP/IP�е�Э�飬�˴�ָ��ʹ��TCPЭ��

//2.��socket�󶨱���ip��ַ�Ͷ˿ں�
	struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(PORT);	//htons()���ѱ����ֽ���ת�������ֽ���
		addr.sin_addr.S_un.S_addr = ADDR_ANY;	//�󶨱�������ip
//3.bind�󶨶˿�
		if (SOCKET_ERROR == bind(fd, (struct sockaddr*)&addr, sizeof(addr)))
		{
			err("bind");
			return INVALID_SOCKET;
		}

//4.��ʼ����
		listen(fd, 10);	//ͬʱ����10���û����з���
	return fd;
}


SOCKET create_clientSocket(const char *ip)
{
	//1.����һ���յ�socket
	SOCKET fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == fd)
	{
		err("socket");
		return INVALID_SOCKET;
	}
	//AF_INET��ָ����ַЭ���壬INETָIPV4
	//SOCK_STREAM��������ʽ�׽���
	//IPPROTO_TCP��ָ��ʹ��TCP/IP�е�Э�飬�˴�ָ��ʹ��TCPЭ��

//2.��socket�󶨷����ip��ַ�Ͷ˿ں�
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);	//htons()���ѱ����ֽ���ת�������ֽ���
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");	//�󶨷�����ip
	if (INVALID_SOCKET == connect(fd, (struct sockaddr*)&addr, sizeof(addr)))
	{
		err("connect");
		return INVALID_SOCKET;
	}

	return fd;
}