/*
  Name: RenjuGame.dev
  Description: ����������Ϸ
  Author: 19301050-wumengning
  Date: 29-06-20 13:00
*/

#include "GUI_display.h"
#include "global.h"
#include "model.h"

int main() { // ������
	int board[15][15] = { 0 }; // �������̲���ʼ��
	initgraph(800, 600); // ��ʼ��ͼ�ν����С
	displayMenu(board); // �˵�
	closegraph(); //�رջ�ͼ����
	return 0;
}