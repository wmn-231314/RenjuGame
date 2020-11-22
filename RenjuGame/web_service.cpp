#include "GUI_display.h"
#include "game_display.h"
#include "web_service.h"


void setWeb(SOCKET *newC,SOCKET *listenS,int character) { // 判断服务器和客户端
	char ip[20];
	if (character) {
		InputBox(ip, 20, "请输入ip地址（xxx.xxx.xxx.xxx）", NULL, NULL, 400, 0); // 获取ip地址
		client(newC,ip); // 初始化并设置客户端，连接服务器
	}
	else {
		server(newC,listenS); // 初始化并设置服务器，连接客户端
	}

}

void server(SOCKET *NewConnection, SOCKET *ListeningSocket) { // 初始化并设置服务器，连接客户端
    int Ret; // 声明变量
    WSADATA wsaData;
    SOCKADDR_IN ServerAddr;
    SOCKADDR_IN ClientAddr;
    int ClientAddrLen = sizeof(ClientAddr);
    unsigned short Port = 5150;


    //初始化 
    if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
    {
        printf("WSASTARTUP_ERROR: %d\n", Ret);
        exit(1);
    }

    //创建一个socket
    if ((*ListeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        printf("SOCKET_ERROR: %d\n", INVALID_SOCKET);
        exit(1);
    }


    /*
     * 填充SOCKADDR_IN结构，这个结构将告知bind我们想要在5150端口监听所有接口上的连接
     */
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(Port); //将端口变量从主机字节顺序转换位网络字节顺序
    ServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);


    //使用bind将这个地址信息和套接字绑定起来
    if (bind(*ListeningSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
    {
        printf("BIND_ERROR: %d\n", SOCKET_ERROR);
        exit(1);
    }

    //监听客户机连接。这里使用5个backlog
    if (listen(*ListeningSocket, 5) == SOCKET_ERROR)
    {
        printf("LISTEN_ERROR: %d\n", SOCKET_ERROR);
        exit(1);
    }

    //连接到达时，接受连接
    while (true) {
        if ((*NewConnection = accept(*ListeningSocket, (SOCKADDR*)&ClientAddr, &ClientAddrLen)) == INVALID_SOCKET) // 若连接不成功，输出动画后尝试重新连接
        {
            disReady(); // 显示等待连接动画
            printf("ACCPET_ERROR: %d\n", INVALID_SOCKET); // 输出错误信息
        }
        else { // 连接成功
            break;
        }
    }
    
 }

void client(SOCKET *newC, char ip[20]) { // 初始化并设置客户端，连接服务器
    int Ret;
    WSADATA wsaData;
    SOCKADDR_IN ServerAddr;
    unsigned short Port = 5150;

    //初始化 
    if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
    {
        printf("WSASTARTUP_ERROR: %d\n", Ret);
        exit(1);
    }

    //创建一个socket
    if ((*newC = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        printf("SOCKET_ERROR: %d\n", INVALID_SOCKET);
        exit(1);
    }

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(Port);
    ServerAddr.sin_addr.S_un.S_addr = inet_addr(ip);// 这里S_un.S_addr在不同的IDE中可能不一样，然后IPv4地址使用该程序所运行在的PC上的IPv4地址

    while (true) {
        if ((connect(*newC, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr))) == SOCKET_ERROR) // 若连接不成功，重新连接
        {
            disReady(); // 显示擂台准备动画
            printf("CONNECT_ERROR: %d\n", SOCKET_ERROR); // 显示提示信息
        }
        else {
            break; // 连接成功
        }
    }
}

void sentChat(SOCKET *NewConnection, int line, int row) { // 发送信息
    char sendData[BUFFSIZE] = {0};
    sprintf_s(sendData, "%d %d", line, row); // 建立传输的字符串
    if (send(*NewConnection, sendData, BUFFSIZE, 0) == SOCKET_ERROR) // 判断是否发送失败
    {
        printf("消息发送失败!\n");
    }
}

Chess* receiveChat(SOCKET *NewConnection) { // 获取信息
    Chess* ch;
    ch = (Chess*)malloc(sizeof(Chess)); // 分配内存
    int Ret, line, row;
    char recvData[BUFFSIZE] = { 0 }; // 初始化
    while (true) {
        Ret = recv(*NewConnection, recvData, BUFFSIZE, 0); // 获取字符串
        if (Ret > 0) {
            sscanf_s(recvData, "%d%d", &line, &row); // 将字符串中有用信息提取出来
            ch->line = line;
            ch->row = row;
        }
        else if (Ret < 0) {
            printf("RECV_ERROR: %d\n", SOCKET_ERROR); // 信息接收失败
        }
        else
        {
            printf("RECV_NOTHING\n");
        }
        if (ch->line < 15 && ch->line >= 0 && ch->row >= 0 && ch->row < 15) { // 判断是否为有用信息
            break;
        }
    }
    return ch; // 返回信息的地址
}

void closeWeb(SOCKET* NewConnection, SOCKET* ListeningSocket, int status) { // 关闭服务器和客户端
    shutdown(*NewConnection, SD_BOTH);
    if (status) { // 判断是服务器还是客户端
        closesocket(*NewConnection);
    }
    else {
        closesocket(*NewConnection);
        closesocket(*ListeningSocket);
    }
    if (WSACleanup() == SOCKET_ERROR) // 判断是否成功关闭
    {
        printf("WSACLEANUP_ERROR: %d\n", WSAGetLastError());
        exit(1);
    }
}

