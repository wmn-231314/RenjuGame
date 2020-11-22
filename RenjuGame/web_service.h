#ifndef _WEB_SERVICE_H
#define _WEBSERVICE_H

#pragma comment(lib,"WSock32.lib")
#include "global.h"
#include "model.h"

 // 网络对战相关函数

#define _CRT_SECURE_NO_WARNINGS
#define BUFFSIZE 1024
#define true 1

void setWeb(SOCKET* newC, SOCKET* listenS, int character); // 判断服务器和客户端
void server(SOCKET* ListeningSocket, SOCKET* NewConnection); // 初始化并设置服务器，连接客户端
void client(SOCKET* newC, char ip[20]); // 初始化并设置客户端，连接服务器
void sentChat(SOCKET *NewConnection, int line, int row); // 发送信息
Chess* receiveChat(SOCKET *NewConnection); // 获取信息
void closeWeb(SOCKET* newConnection, SOCKET* listeningSocket, int status); // 关闭服务器和客户端

#endif // !_WEB_SERVICE_H

