#include "data.h"
#include "game_display.h"
#include "GUI_display.h"

void reviewBoard(int board[15][15]) { // 搜索棋局并回顾
	Winer* head = NULL; // 声明变量并初始化
	Winer* search = NULL;
	char name[100];
	int quit = 0;
	head = loadWiner(); // 加载排名
	if (head == NULL) {
		printf("There isn't any record.\n");
	}
	else {
		while (!quit) { // 是否返回菜单
			quit = disReviewQue(name); // 获得搜索姓名
			if (quit) {
				break; // 返回菜单
			}
			search = head;
			while (search != NULL) { // 遍历链表
				if (strcmp(search->name, name) == 0) {
					displayWinerB(search,board); // 回顾棋局
					break;
				}
				else {
					search = search->next;
				}
			}
		}
	}
}