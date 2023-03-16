#include"../tcpSocket/tcpSocket.h"
#include"../tcpSocket/fileOperation.h"
#include<iostream>


using namespace std;

int main()
{
	init_Socket();
	SOCKET fd = create_clientSocket("127.0.0.1");
	cout << "connect success!" << endl;

//接收服务器传输的数据
	char fileName[100] = { 0 };
	cout << "input filename to save:" << endl;
	cin>>fileName;
	recvFile(fd, fileName);

	closesocket(fd);
	close_Socket();
	
	return 0;
}