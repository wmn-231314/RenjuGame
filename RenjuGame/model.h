#ifndef _MODEL_H
#define _MODEL_H

 // 程序使用结构体

typedef struct record { // 记录棋局所用结构体
	int x;
	int y;
	int chess;
	struct record* next;
}Record;

typedef struct chess { // 记录棋子位置所用结构体
	int line;
	int row;
}Chess;

typedef struct winer { // 记录获胜者生成排名所用结构体
	char name[100];
	int turns;
	struct winer* next;
	Record* winb;
}Winer;

#endif // !_MODEL_H