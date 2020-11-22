#include "GUI_display.h"
#include "game_display.h"
#include "web_service.h"


void setWeb(SOCKET *newC,SOCKET *listenS,int character) { // �жϷ������Ϳͻ���
	char ip[20];
	if (character) {
		InputBox(ip, 20, "������ip��ַ��xxx.xxx.xxx.xxx��", NULL, NULL, 400, 0); // ��ȡip��ַ
		client(newC,ip); // ��ʼ�������ÿͻ��ˣ����ӷ�����
	}
	else {
		server(newC,listenS); // ��ʼ�������÷����������ӿͻ���
	}

}

void server(SOCKET *NewConnection, SOCKET *ListeningSocket) { // ��ʼ�������÷����������ӿͻ���
    int Ret; // ��������
    WSADATA wsaData;
    SOCKADDR_IN ServerAddr;
    SOCKADDR_IN ClientAddr;
    int ClientAddrLen = sizeof(ClientAddr);
    unsigned short Port = 5150;


    //��ʼ�� 
    if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
    {
        printf("WSASTARTUP_ERROR: %d\n", Ret);
        exit(1);
    }

    //����һ��socket
    if ((*ListeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        printf("SOCKET_ERROR: %d\n", INVALID_SOCKET);
        exit(1);
    }


    /*
     * ���SOCKADDR_IN�ṹ������ṹ����֪bind������Ҫ��5150�˿ڼ������нӿ��ϵ�����
     */
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(Port); //���˿ڱ����������ֽ�˳��ת��λ�����ֽ�˳��
    ServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);


    //ʹ��bind�������ַ��Ϣ���׽��ְ�����
    if (bind(*ListeningSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
    {
        printf("BIND_ERROR: %d\n", SOCKET_ERROR);
        exit(1);
    }

    //�����ͻ������ӡ�����ʹ��5��backlog
    if (listen(*ListeningSocket, 5) == SOCKET_ERROR)
    {
        printf("LISTEN_ERROR: %d\n", SOCKET_ERROR);
        exit(1);
    }

    //���ӵ���ʱ����������
    while (true) {
        if ((*NewConnection = accept(*ListeningSocket, (SOCKADDR*)&ClientAddr, &ClientAddrLen)) == INVALID_SOCKET) // �����Ӳ��ɹ����������������������
        {
            disReady(); // ��ʾ�ȴ����Ӷ���
            printf("ACCPET_ERROR: %d\n", INVALID_SOCKET); // ���������Ϣ
        }
        else { // ���ӳɹ�
            break;
        }
    }
    
 }

void client(SOCKET *newC, char ip[20]) { // ��ʼ�������ÿͻ��ˣ����ӷ�����
    int Ret;
    WSADATA wsaData;
    SOCKADDR_IN ServerAddr;
    unsigned short Port = 5150;

    //��ʼ�� 
    if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
    {
        printf("WSASTARTUP_ERROR: %d\n", Ret);
        exit(1);
    }

    //����һ��socket
    if ((*newC = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        printf("SOCKET_ERROR: %d\n", INVALID_SOCKET);
        exit(1);
    }

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(Port);
    ServerAddr.sin_addr.S_un.S_addr = inet_addr(ip);// ����S_un.S_addr�ڲ�ͬ��IDE�п��ܲ�һ����Ȼ��IPv4��ַʹ�øó����������ڵ�PC�ϵ�IPv4��ַ

    while (true) {
        if ((connect(*newC, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr))) == SOCKET_ERROR) // �����Ӳ��ɹ�����������
        {
            disReady(); // ��ʾ��̨׼������
            printf("CONNECT_ERROR: %d\n", SOCKET_ERROR); // ��ʾ��ʾ��Ϣ
        }
        else {
            break; // ���ӳɹ�
        }
    }
}

void sentChat(SOCKET *NewConnection, int line, int row) { // ������Ϣ
    char sendData[BUFFSIZE] = {0};
    sprintf_s(sendData, "%d %d", line, row); // ����������ַ���
    if (send(*NewConnection, sendData, BUFFSIZE, 0) == SOCKET_ERROR) // �ж��Ƿ���ʧ��
    {
        printf("��Ϣ����ʧ��!\n");
    }
}

Chess* receiveChat(SOCKET *NewConnection) { // ��ȡ��Ϣ
    Chess* ch;
    ch = (Chess*)malloc(sizeof(Chess)); // �����ڴ�
    int Ret, line, row;
    char recvData[BUFFSIZE] = { 0 }; // ��ʼ��
    while (true) {
        Ret = recv(*NewConnection, recvData, BUFFSIZE, 0); // ��ȡ�ַ���
        if (Ret > 0) {
            sscanf_s(recvData, "%d%d", &line, &row); // ���ַ�����������Ϣ��ȡ����
            ch->line = line;
            ch->row = row;
        }
        else if (Ret < 0) {
            printf("RECV_ERROR: %d\n", SOCKET_ERROR); // ��Ϣ����ʧ��
        }
        else
        {
            printf("RECV_NOTHING\n");
        }
        if (ch->line < 15 && ch->line >= 0 && ch->row >= 0 && ch->row < 15) { // �ж��Ƿ�Ϊ������Ϣ
            break;
        }
    }
    return ch; // ������Ϣ�ĵ�ַ
}

void closeWeb(SOCKET* NewConnection, SOCKET* ListeningSocket, int status) { // �رշ������Ϳͻ���
    shutdown(*NewConnection, SD_BOTH);
    if (status) { // �ж��Ƿ��������ǿͻ���
        closesocket(*NewConnection);
    }
    else {
        closesocket(*NewConnection);
        closesocket(*ListeningSocket);
    }
    if (WSACleanup() == SOCKET_ERROR) // �ж��Ƿ�ɹ��ر�
    {
        printf("WSACLEANUP_ERROR: %d\n", WSAGetLastError());
        exit(1);
    }
}

