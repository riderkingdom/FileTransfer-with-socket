
#include"../tcpSocket/tcpSocket.h"
#include"../tcpSocket/fileOperation.h"
#include<iostream>

#include<string>

using namespace std;
char* sendBuf;

int main()
{
	init_Socket();

	SOCKET serfd = create_serverSocket();//创建服务器socket（该socket仅用于监听）
	cout << "server create success,wait client connect..." << endl;

	//等待客户端连接
	sockaddr_in caddr;
	caddr.sin_family = AF_INET;
	int caddrlen = sizeof(sockaddr_in);

	SOCKET clifd = accept(serfd, (sockaddr*)&caddr, &caddrlen);	//该socket用于与客户端进行连接
	if (clifd == INVALID_SOCKET)
	{
		err("accept");
	}
	cout << "connect success" << endl;
	//可以与客户端进行通信
	char fileName[100] = { 0 };
	cout << "please input the full path of the file: "<<endl;
	cin >> fileName;
		sendFile(clifd,fileName);


	closesocket(clifd);
	closesocket(serfd);
	close_Socket();
	
	return 0;
}