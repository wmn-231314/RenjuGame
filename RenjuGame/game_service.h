#ifndef _GAME_SERVICE_H
#define _GAME_SERVICE_H

#include "global.h"
#include "model.h"

 // ��Ϸ�߼�����Ӯ�ж���غ���

int judgeLine(int turn, int board[15][15]); // �жϺ���ʤ��
int judgeRow(int turn, int board[15][15]); // �ж�����ʤ��
int judgeSlantR(int turn, int board[15][15]); // �ж���б��ʤ��
int judgeSlantL(int turn, int board[15][15]); // �ж���б��ʤ��
int maxStatus(int, int, int, int, int); // �ж�Ŀǰ���״̬
int drawGame(int board[15][15]); // �ж�ƽ��


#endif // !_GAME_SERVICE_H
