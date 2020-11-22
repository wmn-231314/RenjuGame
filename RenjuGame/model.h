#ifndef _MODEL_H
#define _MODEL_H

 // ����ʹ�ýṹ��

typedef struct record { // ��¼������ýṹ��
	int x;
	int y;
	int chess;
	struct record* next;
}Record;

typedef struct chess { // ��¼����λ�����ýṹ��
	int line;
	int row;
}Chess;

typedef struct winer { // ��¼��ʤ�������������ýṹ��
	char name[100];
	int turns;
	struct winer* next;
	Record* winb;
}Winer;

#endif // !_MODEL_H