#ifndef _WEB_SERVICE_H
#define _WEBSERVICE_H

#pragma comment(lib,"WSock32.lib")
#include "global.h"
#include "model.h"

 // �����ս��غ���

#define _CRT_SECURE_NO_WARNINGS
#define BUFFSIZE 1024
#define true 1

void setWeb(SOCKET* newC, SOCKET* listenS, int character); // �жϷ������Ϳͻ���
void server(SOCKET* ListeningSocket, SOCKET* NewConnection); // ��ʼ�������÷����������ӿͻ���
void client(SOCKET* newC, char ip[20]); // ��ʼ�������ÿͻ��ˣ����ӷ�����
void sentChat(SOCKET *NewConnection, int line, int row); // ������Ϣ
Chess* receiveChat(SOCKET *NewConnection); // ��ȡ��Ϣ
void closeWeb(SOCKET* newConnection, SOCKET* listeningSocket, int status); // �رշ������Ϳͻ���

#endif // !_WEB_SERVICE_H

