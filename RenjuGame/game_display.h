#ifndef _GAME_DISPLAY_H
#define _GAME_DISPLAY_H

#include "model.h"
#include "global.h"

 // ��Ϸ��ʾ��غ���

void startGame(int board[15][15]); // ��ʼ˫����Ϸ
void manMashine(int board[15][15]); // ��ʼ�˻���Ϸ
void rankList(); // ���ز��������
void displayWinerB(Winer* win,int board[15][15]); // ��ȡ������ع����
void startWebGame(SOCKET *newC,int board[15][15],int status); // ��ʼ�����ս


#endif // !_GAME_DISPLAY_H

