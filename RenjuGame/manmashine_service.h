#ifndef _MAN_H
#define _MAN_H

#include "model.h"
#include "global.h"

 // �˻���ս�߼���غ���

void findPos(int board[15][15],int pos[15][15]); // �ҵ����̴��ڵ�����
Chess* maxScore(int score[15][15]); // ���㵱ǰ����״̬��������
void nextScore(int pos[15][15], int score[15][15],int board[15][15]); // ����ÿ��pos��һ���ĵ÷�
int calScore(int different, int same, int blank); // ��ͬ״̬�ķ�ֵ�趨
int scanLine(int l, int r, int status, int board[15][15]); // ���㵱ǰ���߷�ֵ
int scanRow(int l, int r, int status, int board[15][15]); // ���㵱ǰ���߷�ֵ
int scanSlantR(int l, int r, int status, int board[15][15]); // ���㵱ǰ��б�߷�ֵ
int scanSlantL(int l, int r, int status, int board[15][15]); // ���㵱ǰ��б�߷�ֵ
void checkPos(int line, int row, int board[15][15], int pos[15][15]); // �ҵ�������Χ�Ŀ�λpos

#endif // !_MAN_H
