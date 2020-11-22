#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "global.h"

 // ������ʾ��غ���

void displayMenu(int board[15][15]); // ��ʾ�˵�
void disStart(int board[15][15]); // ��ʾ˫�����
void disAbout(); // ��ʾ����
void disRules(); // ��ʾ����
void disSave(char name[100]); // ��ʾ�������
void disManMashine(int board[15][15]); // ��ʾ�˻����
void disWinner(int rank,char name[],int turn); // ��ʾ����
void disChess(int line,int row,int bw); // ��ʾ������������
int disReviewQue(char name[100]); // �ع������ʾ��������
void disChar(int board[15][15]); // ��ʾ��ɫѡ�����
int disConQue(); // ��ʾ�Ƿ�������
void disHint(int bw);// ��ʾ�ִ���ʾ
void disReady(); // ��ʾ��̨׼������
void disSetImg(int but1, int but2); // ��ʾ����ͼƬ
void disSet(int* but1, int* but2); // ����

#endif // !_DISPLAY_H

