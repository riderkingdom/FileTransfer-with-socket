
#include"../tcpSocket/tcpSocket.h"
#include"../tcpSocket/fileOperation.h"
#include<iostream>

#include<string>

using namespace std;
char* sendBuf;

int main()
{
	init_Socket();

	SOCKET serfd = create_serverSocket();//����������socket����socket�����ڼ�����
	cout << "server create success,wait client connect..." << endl;

	//�ȴ��ͻ�������
	sockaddr_in caddr;
	caddr.sin_family = AF_INET;
	int caddrlen = sizeof(sockaddr_in);

	SOCKET clifd = accept(serfd, (sockaddr*)&caddr, &caddrlen);	//��socket������ͻ��˽�������
	if (clifd == INVALID_SOCKET)
	{
		err("accept");
	}
	cout << "connect success" << endl;
	//������ͻ��˽���ͨ��
	char fileName[100] = { 0 };
	cout << "please input the full path of the file: "<<endl;
	cin >> fileName;
		sendFile(clifd,fileName);


	closesocket(clifd);
	closesocket(serfd);
	close_Socket();
	
	return 0;
}