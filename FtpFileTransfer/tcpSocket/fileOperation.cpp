#include"fileOperation.h"
#include<iostream>


using namespace std;

long bufSize = 10*1024;	//��������С
char* buffer;	//�����������ļ�����
//long recvSize = 10000000;
//char* recvBuf;

bool sendFile(SOCKET s, const char* fileName)
{
	FILE* read = fopen(fileName, "rb");
	if (!read)
	{
		perror("file open failed:\n");//��������Դ�����Ϣ
		return false;
	}

//��ȡ�ļ���С
	fseek(read, 0, SEEK_END);	//���ļ�λ��ָ���ƶ������
	bufSize = ftell(read);	//ftell(FILE *stream)�����ظ�����stream�ĵ�ǰ�ļ�λ�ã���ȡ��ǰλ������ļ��׵�λ�ƣ�λ��ֵ�����ļ������ֽ���
	fseek(read, 0, SEEK_SET);	//���ļ�λ��ָ���ƶ�����ͷ
	cout<<"filesize:"<<bufSize<< endl;

//���ļ������ڴ�����
	buffer= new char[bufSize];
	cout << sizeof(buffer) << endl;
	if (!buffer)
	{
		return false;
	}

	int nCount;
	int ret = 0;
	while ((nCount = fread(buffer, 1, bufSize, read)) > 0)	//ѭ����ȡ�ļ����д���
	{
		ret += send(s, buffer, nCount, 0);
		if (ret == SOCKET_ERROR)
		{
			err("sendFile");
			return false;
		}
	}
	shutdown(s, SD_SEND);
	recv(s, buffer, bufSize, 0);
	fclose(read);

	cout << "send file success!"<<" Byte:"<<ret << endl;
	system("pause");
	return true;
}

bool recvFile(SOCKET s, const char* fileName)
{

	if (buffer == NULL)
	{
		buffer = new char[bufSize];
		if (!buffer)
			return false;
	}
//	�������ļ�
	FILE* write = fopen(fileName, "wb");
	if (!write)
	{
		perror("file write failed:\n");
		return false;
	}

	int ret = 0;
	int nCount;
	while ((nCount = recv(s, buffer, bufSize, 0)) > 0)	//ѭ�������ļ�������
	{
		ret += fwrite(buffer,nCount, 1, write);
	}
	if (ret == 0)
	{
		cout << "server offline" << endl;
	}
	else if(ret < 0)
	{
		err("recv");
		return false;
	}
	cout << "receive file success!" << endl;

	fclose(write);
	cout << "save file success! Filename:"<<fileName << endl;
	system("pause");
	return true;
}