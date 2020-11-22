#include "data.h"
#include "game_display.h"
#include "GUI_display.h"

void reviewBoard(int board[15][15]) { // ������ֲ��ع�
	Winer* head = NULL; // ������������ʼ��
	Winer* search = NULL;
	char name[100];
	int quit = 0;
	head = loadWiner(); // ��������
	if (head == NULL) {
		printf("There isn't any record.\n");
	}
	else {
		while (!quit) { // �Ƿ񷵻ز˵�
			quit = disReviewQue(name); // �����������
			if (quit) {
				break; // ���ز˵�
			}
			search = head;
			while (search != NULL) { // ��������
				if (strcmp(search->name, name) == 0) {
					displayWinerB(search,board); // �ع����
					break;
				}
				else {
					search = search->next;
				}
			}
		}
	}
}